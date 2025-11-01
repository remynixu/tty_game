#include "mem.h"

#ifndef NULL
#define NULL	((void *)0)
#endif /* NULL */

/*
 * How do we allocate memory?
 *
 * 	FORMATTING MEMORY INTO BLOCKS
 * First, we format our byte buffer into something we can work with. This format
 * is called a block. It contains the following sections:
 * - Header       - Contains the memory size and block status, located at the
 *                  beginning of the block.
 *                - Alias: 'hdr'
 * - Memory       - Contains the usable raw buffer that is allocatable or vice
 *                  versa.
 *                - Alias: 'mem'
 * It also contains the following informations:
 * - Block size   - The size of the entire block, is not less than the value of
 *                  HEADER_BYTEWIDTH.
 *                - Alias: 'blk_sz'
 * - Memory size  - The size of the memory contained within the block, is not 
 *                  equal or less than the value of HEADER_BYTEWIDTH.
 *                - Alias: 'mem_sz'
 * - Block status - Holds the status of the block, used for defining the current
 *                  options for the block.
 *                - Here are the possible status:
 *                  - BLOCK_AVAIL
 *                  - BLOCK_GIVEN
 *                - Alias: 'blk_sts'
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
 * 	MANIPULATING A BLOCK
 * Now that we have a block, we can start managing it. This is also the part
 * where the process of allocation and freeing is described:
 * - Allocation   - To allocate a block, we first split a block into two. One
 *                  for the requested memory size, and another free block, valid
 *                  for another allocation.
 * - Freeing      - To free a block, we reformat the block into a free one. And
 *                  if possible, merge it with another free block.
 *
 * 	RATIONALE
 * Why a block? It is simple enough for me, and I don't see why I should go all
 * out on such a silly and unserious library...
 */

#define MEMSZ_BYTEWIDTH	sizeof(unsigned long)
#define STATUS_BYTEWIDTH	sizeof(unsigned long)
#define HEADER_BYTEWIDTH	(MEMSZ_BYTEWIDTH + STATUS_BYTEWIDTH)

static unsigned long to_memsz(unsigned long blk_sz){
	return blk_sz - HEADER_BYTEWIDTH;
}

static unsigned long to_blksz(unsigned long mem_sz){
	return mem_sz + HEADER_BYTEWIDTH;
}

static void memcpyul(void *buf, unsigned long ul){
	*(unsigned long *)buf = ul;
}

static unsigned long *_memsz_pos(void *blk){
	return blk;
}

static unsigned long _memsz(void *blk){
	return *_memsz_pos(blk);
}

static unsigned long *_flag_pos(void *blk){
	return _memsz_pos(blk) + 1;
}

static unsigned long _flag(void *blk){
	return *_flag_pos(blk);
}

static void *_mem_pos(void *blk){
	return _flag_pos(blk) + 1;
}

#define BLOCK_AVAIL	(0 << 0)
#define BLOCK_GIVEN	(1 << 0)

static void *__blkfmt(void *buf, unsigned long blk_sz, int sts){
	memcpyul(buf, to_memsz(blk_sz));
	memcpyul(_flag_pos(buf), sts);
	return buf;
}

#define BLKCOUNT_BYTEWIDTH	sizeof(unsigned long)

static void *_main_block_fmt(void *buf, unsigned long blk_sz){
	memcpyul(buf, 0);
	__blkfmt((char *)buf + BLKCOUNT_BYTEWIDTH, blk_sz - BLKCOUNT_BYTEWIDTH,
			BLOCK_AVAIL);
	return buf;
}

void *blkfmt(void *buf, unsigned long sz){
	void *ret;
	if(sz < HEADER_BYTEWIDTH){
		ret = NULL;
		goto out;
	}
	buf = _main_block_fmt(buf, sz);
	ret = buf;
out:
	return ret;
}
