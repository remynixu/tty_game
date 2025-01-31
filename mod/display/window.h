#ifndef WINDOW_H
#define WINDOW_H	1

#include "./gridbox.h"

#include <stdio.h>

struct window{
	struct gridbox *gboxes;
	unsigned char width;
	unsigned char height;
};

extern int fput_wnd(FILE *fstream, struct window *wnd);

#endif
