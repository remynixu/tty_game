#ifndef GRIDBOX_H
#define GRIDBOX_H	1

#include "./color.h"

struct gridbox{
	unsigned char clrinfo;
	char icon;
};

extern int isvalgbox(struct gridbox gbox);
extern int fputgbox(FILE *f, struct gridbox gbox);

#endif /* GRIDBOX_H */
