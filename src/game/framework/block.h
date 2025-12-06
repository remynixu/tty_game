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

/*
 * Constants :>
 *
 * This could be a standalone library if "NULL" and "size_t" are defined.
 */

#include "presets.h"



/*
 * To use the library's functions, a buffer of raw bytes must be formatted into
 * a "block" (blk). From now on, it will be referred to without the quotations.
 *
 * `buf` expects the buffer, and `sz` expects the size of the buffer in bytes.
 */

void *blkfmt(void *buf, size_t sz);

/*
 * A block, when split, is usually supposed to be treated like a linked list.
 * But these options give choices on this matter.
 *
 * KEEPLINK - "Keeps" the link of the first half after split by storing it's
 *            link to the second half. But, if LINK2TO1 is active , the link of
 *            the second half is kept by storing it in the first half instead.
 * LINK1TO2 - Link the first half to the second, overrides the KEEPLINK option.
 * LINK2TO1 - Link the second half to the first, overrides the KEEPLINK option.
 * GIVEBLK1 - Marks the first half as "given", thus making it unsplitable.
 * GIVEBLK2 - Marks the second half as "given", thus making it unsplitable.
 */

enum blksplit_mode{
	KEEPLINK,
	LINK1TO2,
	LINK2TO1,
	GIVEBLK1,
	GIVEBLK2
};

/*
 * Splits a block, the function that makes "allocating" possible.
 *
 * `blk` expects a "free" block - a block that isn't given (thanks captain
 * obvious...) - or else, the function simply returns NULL. `payload_sz` expects
 * the memory size that the second half - the returned block - will have. And
 * lastly, `how` expects the "flags" from above this. Note that the flags can be
 * "or'ed" to achieve more specific results like so:
 *
 * // Random fact, this is actually the intended use of blksplit(). It is used
 * // to imitate the allocating behavior of malloc() from stdlib.h! Just make
 * // sure to pass the same block in `blk` for the next call and store the
 * // returned pointer to another void pointer.
 * blksplit(blk, 100, KEEPLINK | GIVEBLK2 | LINK1TO2);
 *
 * // Reverse linked list?
 * blksplit(blk, 100, KEEPLINK | GIVEBLK1 | LINK2TO1);
 *
 * Note:
 * 
 * If `how` has no value, the two halves will be marked as free and will no
 * links, essentially making two heads of a linked list if treated like so.
 */

void *blksplit(void *blk, size_t payload_sz, enum blksplit_mode how);

/* WIP */
int blkmerge(void *blk1, void *blk2);



#endif /* BLOCK_H */
