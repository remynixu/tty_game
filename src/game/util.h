#ifndef UTIL_H
#define UTIL_H

/* MATH */

#define XYWTOI(x, y, w)	((x) + (y) * (w))

/* BIT */

#define BIT(n)	(1ULL << (n))
#define BITFIELD(sz, i)	((BIT(sz) - 1) << (i))

#define GETFIELD(b, sz, i)	(((b) >> (i)) & (sz))

#define BITSWAP(a, b){	\
	(a) = (a) ^ (b);	\
	(b) = (a) ^ (b);	\
	(a) = (a) ^ (b);	\
}

#define ERROR(type)	BITFIELD(sizeof(type) * 8, 0)

/* IO */

int input_raw(void);
int print_raw(char *str);

/* STRINGS*/

char itoc(int i);
char *itoa(int i, int base);

#endif
