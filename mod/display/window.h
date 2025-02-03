#ifndef WINDOW_H
#define WINDOW_H	1

#include "./gridbox.h"

struct window{
	struct gridbox *gboxes;
	unsigned char width;
	unsigned char height;
};

extern int mkwnd(struct window *wnd);
extern int isvalwnd(struct window *wnd);
extern int fput_wnd(FILE *f, struct window *wnd);

#endif /* WINDOW_H */
