#include "mem.h"

#ifndef NULL
#define NULL	((void *)0)
#endif /* NULL */

/*
 * How do we allocate memory?
 *
 * 	FORMATTING MEMORY INTO BLOCKS
 * First, we format our byte buffer into something we can work with. This format
 * is called a block. It must contain the following:
 * - Block size   - The size of the entire block, is not less than the value of
 *                  BLOCK_METADATA_BYTEWIDTH.
 *                - Alias: 'sz'
 * - Block status - Holds the status of the block, used for defining the current
 *                  options for the block.
 *                - Here are the possible status:
 *                  - BLOCK_FREE
 *                  - BLOCK_USED
 *                - Alias: 'sts'
 * - Memory size  - The size of the memory contained within the block, is not 
 *                  equal or less than the value of BLOCK_METADATA_BYTEWIDTH.
 *                - Alias: 'mem_sz'
 * Block sections:
 * - Header       - Contains the Memory size, located at the beginning of the
 *                  block.
 *                - Alias: 'hdr'
 * - Memory       - Contains the usable raw buffer that is allocatable or vice
 *                  versa.
 *                - Alias: 'mem'
 * - Footer       - Contains the Block status, located at the end of the block.
 *                - Alias: 'ftr'
 *
 * 	MANIPULATING A BLOCK
 * Now that we have a block, we can start managing it. This is also the part
 * where the process of allocation and freeing is described:
 * - Allocation   - To allocate a block, we first split a block into two. One for
 *                  the requested memory size, and another free block, valid for
 *                  another allocation.
 * - Freeing      - To free a block, we reformat the block into a free one. And if
 *                  possible, merge it with another free block.
 *
 * 	TRACKING THE BLOCKS
 * Splitting blocks are fine, but how do we track how many blocks are there? We
 * need to do so to also track the amount of bytes we are working with.
 * - Block count  - Only applies to the first/main block, tracks the amount of
 *                  blocks, especially after functions split or merge blocks in
 *                  the main block.
 *                - Alias: 'cnt', 'main'
 *
 * 	EXTRA BLOCK INFORMATION
 * For extra information, some systems require specific byte alignments. We can
 * compensate by making functions take the macro MEMORY_ALIGNMENT into account.
 *
 * 	RATIONALE
 * Why a block? It is simple enough for me, and I don't see why I should go all
 * out on such a silly and unserious library...
 */

#define HEADER_BYTEWIDTH	sizeof(unsigned long)
#define FOOTER_BYTEWIDTH	sizeof(unsigned char)
#define METADATA_BYTEWIDTH	(HEADER_BYTEWIDTH + FOOTER_BYTEWIDTH)

static void _header(void *hdr, unsigned long mem_sz){
	unsigned long *h = (unsigned long *)hdr;
	*h = mem_sz;
}

static unsigned long _to_memsz(unsigned long sz){
	return sz - METADATA_BYTEWIDTH;
}

static unsigned long _to_sz(unsigned long memsz){
	return memsz + METADATA_BYTEWIDTH;
}

static unsigned long _memsizeof_block(void *hdr){
	return *(unsigned long *)hdr;
}

static unsigned long _sizeof_block(void *blk){
	return _to_sz(_memsizeof_block(blk));
}

static void *_memory_pos(void *blk){
	return (char *)blk + HEADER_BYTEWIDTH;
}

static void *_header_pos(void *mem_pos){
	return (char *)mem_pos - HEADER_BYTEWIDTH;
}

static void _memory(void *mem, unsigned long mem_sz){
	unsigned long i = 0;
	unsigned char *m = (unsigned char *)mem;
	for(; i < mem_sz; i++)
		m[i] = 0;
}

static void *_footer_pos(void *blk){
	return (char *)blk + _memsizeof_block(blk);
}

static void _footer(void *ftr, unsigned char sts){
	unsigned char *f = (unsigned char *)ftr;
	*f = sts;
}

static unsigned char _flagof_block(void *blk){
	return *(unsigned char *)_footer_pos(blk);
}

#define BLOCK_FREE	(1 << 0)
#define BLOCK_USED	(1 << 1)

static void *__blkfmt(void *blk, unsigned long sz, unsigned char sts){
	/* Assumes that 'blk' is the start of the buffer to format. */
	_header(blk, _to_memsz(sz));
	_memory(_memory_pos(blk), _to_memsz(sz));
	_footer(_footer_pos(blk), sts);
	return blk;
}

static void *_main_block(void *buf, unsigned long sz){
	_header(buf, 1); /* annoying hack */
	buf = (void *)((char *)buf + HEADER_BYTEWIDTH);
	sz -= HEADER_BYTEWIDTH;
	return (char *)__blkfmt(buf, sz, BLOCK_FREE) - HEADER_BYTEWIDTH;
}

/*
 * 'main' == 'The counter of the blocks'
 */

static unsigned long *_count_pos(void *main){
	return (unsigned long *)main;
}

static unsigned long _countof_block(void *main){
	return *_count_pos(main);
}

/*
 * Unlike __blkfmt() which returns a normal block, this must only return a main
 * block. It isn't made for most private uses, use __blkfmt() for that instead.
 */

void *blkfmt(void *buf, unsigned long sz){
	void *blk = NULL;
	if(!buf)
		goto out;
	if(sz < METADATA_BYTEWIDTH)
		goto out;
	blk = _main_block(buf, sz);
out:
	return blk;
}

static void *_next_block(void *sub_blk){
	return (char *)sub_blk + METADATA_BYTEWIDTH + _memsizeof_block(sub_blk);
}

#define BLOCK_SUB	(1 << 0)
#define BLOCK_ADD	(1 << 1)

static void _set_block_counter(void *main, unsigned char how){
	unsigned long *cnt = _count_pos(main);
	if(how & BLOCK_SUB)
		(*cnt)--;
	if(how & BLOCK_ADD)
		(*cnt)++;
}

/*
 * Do we really need the user to use this?
 * - No, we do not need the user manually splitting blocks. That's our job ^-^
 */

static void *_split_block(void *main, void *sub_blk, unsigned long sz,
		unsigned char sts1, unsigned char sts2){
	unsigned long sz2 = _sizeof_block(sub_blk) - sz;
	void *sub_blk2;
	sub_blk = __blkfmt(sub_blk, sz, sts1);
	sub_blk2 = __blkfmt(_next_block(sub_blk), sz2, sts2);
	_set_block_counter(main, BLOCK_ADD);
	return sub_blk2;
}

static void *_find_block(void *main, unsigned char sts){
	/* Another hack only works because block counter is as wide as a
	 * header. */
	void *sub_blk = _memory_pos(main);
	unsigned long cnt = _countof_block(main);
	unsigned long i = 0;
	for(; i < cnt; i++, sub_blk = _next_block(sub_blk)){
		if(_flagof_block(sub_blk) & sts)
			break;
	}
	if(i == cnt)
		sub_blk = NULL;
	return sub_blk;
}

static int _is_mergeable(void *sub_blk1, void *sub_blk2){
	if(_flagof_block(sub_blk1) & BLOCK_USED)
		return 0;
	if(_flagof_block(sub_blk2) & BLOCK_USED)
		return 0;
	if(_next_block(sub_blk1) != sub_blk2)
		return 0;
	return 1;
}

/*
 * Assume that both 'sub_blkn' are approved by the _is_mergeable() function.
 */

static void *_merge_block(void *main, void *sub_blk1, void *sub_blk2){
	unsigned long sz = _sizeof_block(sub_blk1) + _sizeof_block(sub_blk2);
	_set_block_counter(main, BLOCK_SUB);
	return __blkfmt(sub_blk1, sz, BLOCK_FREE);
}

/* original names hehe */

void *hold(void *blk, unsigned long mem_sz){
	unsigned long sz = _to_sz(mem_sz);
	void *free_blk = _find_block(blk, BLOCK_FREE);
	void *res = NULL;
	if(!free_blk)
		goto out;
	if(!blk)
		goto out;
	if(_sizeof_block(free_blk) < sz)
		goto out;
	res = _split_block(blk, free_blk, sz, BLOCK_USED, BLOCK_FREE);
out:
	return _memory_pos(res);
}

void release(void *blk, void *mem_ptr){
	void *sub_blk = _header_pos(mem_ptr);
	void *free_blk = _find_block(blk, BLOCK_FREE);
	unsigned long sz = _sizeof_block(blk);
	__blkfmt(sub_blk, sz, BLOCK_FREE);
	if(!_is_mergeable(sub_blk, free_blk))
		return;
	_merge_block(blk, sub_blk, free_blk);
}
