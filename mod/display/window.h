#ifndef WINDOW_H
#define WINDOW_H	1

#include "grid.h"

#include <stdio.h>

/*
 * Go set one up yourself.
 */
struct window{
	struct gridbox *gboxes;
	unsigned char width;
	unsigned char height;
};

/*
 * Put wnd to fstream.
 * Return 0, EINVAL, or EOF.
 */
extern int fput_wnd(FILE *fstream, struct window *wnd);

#endif
