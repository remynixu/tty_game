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
 * - Block status - Holds the status of the block, used for defining the current
 *                  options for the block.
 *                - Here are the possible status:
 *                  - BLOCK_FREE
 *                  - BLOCK_USED
 * - Memory size  - The size of the memory contained within the block, is not 
 *                  equal or less than the value of BLOCK_METADATA_BYTEWIDTH.
 * Block sections:
 * - Header       - Contains the Memory size, located at the beginning of the
 *                  block.
 * - Memory       - Contains the usable raw buffer that is allocatable or vice
 *                  versa.
 * - Footer       - Contains the Block status, located at the end of the block.
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

static void *_memory_pos(void *blk){
	return (char *)blk + HEADER_BYTEWIDTH;
}

static void _memory(void *mem, unsigned long mem_sz){
	unsigned long i = 0;
	unsigned char *m = (unsigned char *)mem;
	for(; i < mem_sz; i++)
		m[i] = 0;
}

static void *_footer_pos(void *blk){
	return (char *)blk + FOOTER_BYTEWIDTH;
}

static void _footer(void *ftr, unsigned char sts){
	unsigned char *f = (unsigned char *)ftr;
	*f = sts;
}

static unsigned long _to_memsz(unsigned long sz){
	return sz - METADATA_BYTEWIDTH;
}

#define BLOCK_FREE	0
#define BLOCK_USED	1

static void *__blkfmt(void *blk, unsigned long sz, unsigned char sts){
	/* Assumes that 'blk' is the start of the buffer to format. */
	_header(blk, _to_memsz(sz));
	_memory(_memory_pos(blk), _to_memsz(sz));
	_footer(_footer_pos(blk), sts);
	return blk;
}

static void *_main_block(void *buf, unsigned long sz){
	_header(buf, 1);
	buf = (void *)((char *)buf + HEADER_BYTEWIDTH);
	sz -= HEADER_BYTEWIDTH;
	return (char *)__blkfmt(buf, sz, BLOCK_FREE) - HEADER_BYTEWIDTH;
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

/* TODO: split(), free(), and merge(). */
