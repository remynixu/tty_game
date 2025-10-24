#ifndef MEM_H
#define MEM_H

/*
 * This is a library that uses any provided memory pools for allocating memory.
 * It doesn't require any standard library whatsoever. It is not exactly built
 * for 64-bit machines, but it should work...
 * 
 * Made for fun! XD
 *
 * - remynixu
 */

/*
 * Takes a formatted buffer from the 'to_block()' function and returns info
 * about the block.
 */

unsigned long block_memsize(void *blk);
unsigned long block_size(void *blk);
unsigned long block_freesize(void *blk);

/*
 * Formats a buffer into a block. Takes a raw buffer and only formats up to the
 * size specified, the block will have the attributes specified by the flags.
 *
 * Only pick one alignment value and 'or' it with the free flag (or not), the
 * max value of alignment is 127 or ((1 << 7) - 1).
 */

#define FREE_SPACE	(1 << 7)

int to_block(void *buf, unsigned long sz, char flags);

#endif
