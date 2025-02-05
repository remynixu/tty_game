#ifndef GRIDBOX_H
#define GRIDBOX_H	1

#include "./color.h"

struct gridbox{
	/* see color.h for info about packed_clr. */
	unsigned char packed_clr;
	char icon;
};

extern struct gridbox mkgbox(char icon, unsigned char packed_clr);

extern int isvalgbox(struct gridbox gbox);
extern int putgbox(struct gridbox gbox);

#endif /* GRIDBOX_H */
