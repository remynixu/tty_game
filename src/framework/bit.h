#ifndef BIT_H
#define BIT_H

/* Make a data with the specified bit index enabled. */
#define BIT(i)	(1ULL << (i))

/* Make a data with the specified number of bits enabled. */
#define BITMASK(n)	(BIT(n) - 1)

/* Get a specified number of bits in a bitmask format. */
#define BITMASKGET(b, n, i)	(((b) >> (i)) & BITMASK(n))

/* Make a data with the specified number of bits enabled at a specified index. */
#define BITFIELD(n, i)	(BITMASK(n) << (i))

/* Remove a bit in a data. */
#define BITRM(b, i)	((b) & ~BIT(i))

/* Set a bit in a data. */
#define BITSET(b, i, v)	((v) ? (b) | BIT(i) : BITRM(b, i))

#endif
