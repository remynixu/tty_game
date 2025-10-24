#include "mem.h"



/*
 * Utilities...
 */

#ifndef NULL

#define NULL	((void *)0)

#endif /* NULL */

#ifndef STD_ERRNO

#define EINVAL	1
#define ENOMEM	2

#else

#include <errno.h>

#endif /* STD_ERRNO */

static void *__memcpy(void *dst, void *src, unsigned long sz){
	char *s = src, *d = dst;
	unsigned long i = 0;
	for(; i < sz; d[i] = s[i], i++); 
	return dst;
}

static void *__memset(void *dst, unsigned char src, unsigned long sz){
	char *d = dst;
	unsigned long i = 0;
	for(; i < sz; d[i] = src, i++);
	return dst;
}

#define PASS	1
#define _reverse_bool(val)	((v) ? 0 : 1)
#define _check_zero(a, b, c)	_reverse_bool((a) && (b) && (c))



/*
 * A block is a formatted buffer of bytes, abbreviated as 'blk'.
 *
 * It is composed of:
 * > Header	- Contains the size of the 'Memory' section, located at the
 * 		  start of the block. Can be abbreviated as 'hdr'.
 * > Memory	- The memory allocated for use, located after the header.
 * 		  Can be abbreviated as 'mem'.
 * > Footer	- Contains the info about the block's status, located after the
 * 		  memory. Can be abbreviated as 'ftr'. It is composed of:
 * 		> Align value	- A 7 bit wide value that dictates the block's
 * 				  alignment.
 * 		> Free flag	- 8th bit that is active when the block is not
 * 				  used.
 */

/*
 * There are two kinds of sizes that the library works with, block size and
 * memory size.
 * > Block size		- The size of the entire block.
 * > Memory size	- The size of the memory section of the block.
 *
 * Here are the functions for converting values.
 */

static unsigned long _blksz_to_memsz(unsigned long blk_sz){
	return blk_sz - HEADER_BYTESIZE - FOOTER_BYTESIZE;
}

static unsigned long _memsz_to_blksz(unsigned long mem_sz){
	return mem_sz + HEADER_BYTESIZE - FOOTER_BYTESIZE;
}

/*
 * Functions for creating and locating each part of a block.
 */

static void *_header_pos(void *buf){
	return buf;
}

#define HEADER_BYTESIZE	sizeof(unsigned long)

static void *_header_fmt(void *hdr_p, unsigned long blk_sz){
	unsigned long mem_sz = _blksz_to_memsz(blk_sz);
	return __memcpy(hdr_p, &mem_sz, HEADER_BYTESIZE);
}

static void *_memory_pos(void *buf){
	return (char *)buf + HEADER_BYTESIZE;
}

static void *_memory_fmt(void *mem_p, unsigned long blk_sz, char val){
	return __memset(mem_p, val, _blksz_to_memsz(blk_sz));
}

static void *_footer_pos(void *buf){
	return (char *)buf + HEADER_BYTESIZE + block_memsize(buf);
}

#define FOOTER_BYTESIZE	sizeof(char)

static void *_footer_fmt(void *ftr_p, char flags){
	return __memcpy(ftr_p, &flags, FOOTER_BYTESIZE);
}

/*
 * Functions for getting information from the 'raw buffer' version of a block.
 */

unsigned long block_memsize(void *blk){
	return *(unsigned long *)buf;
}

unsigned long block_size(void *blk){
	return _memsz_to_blksz(block_memsize(blk));
}

unsigned long block_freesize(void *blk){
	unsigned long cnt = 0;
	unsigned long i = 0;
	char *blk_p = (char *)_memory_pos(blk);
	for(; i < block_memsize(blk); i++, cnt++, blk_p++){
		if(*blk_p == 0)
			continue;
		break;
	}	
	return cnt;
}

/*
 * These functions create and manipulate a block.
 */

#define _mask_bit(b, n)	((b) & ~(1 << (n)))
#define _snap_num(n, v)	((v) ? ((n) + ((n) % (v))) : (n))
#define _check_flag(b, f)	((b) & (f))

static void *__to_block(void *buf, unsigned long blk_sz, char flags){
	unsigned char alignment = _mask_bit(flags, 7);
	unsigned long aligned_sz = _snap_num(blk_sz, alignment);
	char mem_content = _reverse_bool(_check_flag(flags, FREE_SPACE));
	_header_fmt(_header_pos(buf), aligned_sz);
	_memory_fmt(_memory_pos(buf), aligned_sz, mem_content);
	_footer_fmt(_footer_pos(buf), flags);
	return buf;
}

int to_block(void *buf, unsigned long sz, char flags){
	int ret = 0;
	if(_check_zero(PASS, buf, sz)){
		ret = EINVAL;
		goto out;
	}
	__to_block(buf, sz, flags);
out:
	return ret;
}

void *_next_block(void *blk){
	return (char *)blk + block_size(blk);
}

/*
 * To allocate a memory from a block, it is split into two. One block for the
 * requested memory size, and another remainder for the next allocation process.
 */

static void *__split_block(void *blk, unsigned long new_blksz, char flags){
	__to_block(blk, block_size(blk) - new_blksz, flags);
	return __to_block(_next_block(blk), new_blksz, flags);
}

int split_block(void *dst, void *blk, unsigned long mem_sz, char flags){
	int ret = 0;
	unsigned long new_blksz = _memsz_to_blksz(mem_sz);
	if(_check_zero(dst, blk, mem_sz)){
		ret = EINVAL;
		goto out;
	}
	if(block_freesize(blk) < mem_sz){
		ret = ENOMEM;
		goto out;
	}
	dst = __split_block(blk, new_blksz, flags);
out:
	return ret;
}
