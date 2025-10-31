#ifndef MEM_H
#define MEM_H

/*
 * This is a library that uses any provided memory pools for allocating memory.
 * It doesn't require any standard library whatsoever, it only needs the C90
 * standard. It is not exactly built for 64-bit machines, but it should work...
 * 
 * Made for fun! XD
 *
 * - remynixu
 */

/* TODO: test it out! */

void *blkfmt(void *buf, unsigned long sz);
void *hold(void *blk, unsigned long mem_sz);
void release(void *blk, void *mem_ptr);

#endif /* MEM_H */
