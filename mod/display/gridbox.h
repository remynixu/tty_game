#ifndef GRID_H
#define GRID_H		1

#include "color.h"

#include <stdio.h>

#define gbox_default	{color_clear, '?'}

struct gridbox{
	struct color *color;
	char icon;
};

/*
 * Put a gbox to fstream.
 * Return 0 or EOF.
 */
extern int fput_gridbox(FILE *fstream, struct gridbox *gbox);

/*
 * Check if gbox is valid.
 * Return 0(invalid) or 1(valid)
 */
extern int isvalgbox(struct gridbox *gbox);

#endif
