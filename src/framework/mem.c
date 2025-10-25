#include "mem.h"

/*
 * To manage a memory, it's size and status must be properly identified.
 *
 * A block is used to make memory pools easier to manage. It has information
 * about the memory's size and status (whether it's free or not).
 *
 * Byte alignment is defined by the 'MEM_ALIGNMENT' macro, changeable by the
 * user.
 *
 * Block sections:
 * - The header section will have a width defined by the HEADER_BYTEWIDTH macro,
 *   enough to hold the value that contains the size of the memory section.
 * - The memory section will be simple: if the memory is free, the bytes will
 *   hold the value of the FREE_MEM macro. Else, the bytes will hold the value
 *   of the USED_MEM macro.
 *
 * Block informations:
 * - 'size/sz' is the size of the entire block.
 * - 'memsize/memsz' is the size of the memory section.
 * - 'status/stat' defines whether the block is free or not.
 *
 * Block processes:
 * - To 'allocate', the block will be split into two. One for the requested
 *   memory size, and the other will be free for more allocations.
 * - To 'free' a memory, the block is simply be reformatted as a free block and
 *   if possible, merged with other blocks to form a big free block.
 */

#define MEM_ALIGNMENT	sizeof(unsigned long)
#define HEADER_BYTEWIDTH	sizeof(unsigned long)
#define FREE_MEM	1
#define USED_MEM	0

static void *_header_pos(void *buf){
	return buf;
}

static void _header_fmt(void *hdr, unsigned long memsz){
	*hdr = memsz;
}

static void *_mem_pos(void *buf){
	return (char *)buf + HEADER_BYTEWIDTH;
}

static unsigned long _to_memsz(unsigned long sz){
	return sz - HEADER_BYTEWIDTH;
}

static void _mem_fmt(void *mem, unsigned long memsz, unsigned char stat){
	unsigned long i = 0;
	for(; i < sz; i++)
		mem[i] = stat;
}

void *blkfmt(void *buf, unsigned long sz, unsigned char stat){
	_header_fmt(_header_pos(buf), _to_memsz(sz));
	_memory_fmt(_mem_pos(buf), _to_memsz(sz), stat);
	return buf;
}
