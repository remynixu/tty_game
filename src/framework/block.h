#ifndef BLOCK_H
#define BLOCK_H

/*
 * Hi! This library used to be 'blk.h' but was later renamed for clarity at the
 * cost of brevity (not really, the naming is kinda meh :P)
 *
 * This library give malloc-like functionality to definable memory sources. It
 * only requires the C90 without any need for the standard libraries!
 *
 * Made for fun! XD
 *
 * - remynixu
 */

#ifndef NULL
#define NULL	((void *)0)
#endif /* NULL */

typedef unsigned long blk_size_t;

int blkerr(void);
char *blk_strerror(void);

void dump_byte(char c, int (*putchar_fn)(int));

void *blkfmt(void *buf, blk_size_t sz);
void blkdump(void *blk, int (*putchar_fn)(int), blk_size_t nl);
void *blkalloc(void *blk, blk_size_t sz);

#endif /* BLOCK_H */
