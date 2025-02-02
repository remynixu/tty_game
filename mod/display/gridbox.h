#ifndef GRID_H
#define GRID_H		1

#include <stdio.h>

#include "./color.h"

struct gridbox{
	struct color *color;
	char icon;
};

extern int fput_gridbox(FILE *fstream, struct gridbox *gbox);
extern int isvalgbox(struct gridbox *gbox);

#endif
