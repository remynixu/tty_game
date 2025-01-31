#ifndef GRID_H
#define GRID_H		1

#include "./color.h"

#include <stdio.h>

struct gridbox{
	struct color *color;
	char icon;
};

extern struct gridbox gbox_empty;

extern int fput_gridbox(FILE *fstream, struct gridbox *gbox);
extern int isvalgbox(struct gridbox *gbox);

#endif
