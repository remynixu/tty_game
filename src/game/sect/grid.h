#ifndef GRID_H
#define GRID_H

#include "../wnd.h"

struct grid{
	char icon;
	unsigned char clr;
	unsigned char x;
	unsigned char y;
};

extern void wputgrid(struct wnd *wnd,
		struct grid grid);

#endif /* GRID_H */
