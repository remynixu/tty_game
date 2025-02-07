#ifndef WINDOW_H
#define WINDOW_H	1

#include "./gridbox.h"

struct window{
	struct gridbox *gboxes;
	unsigned char width;
	unsigned char height;
};

extern struct window mkwnd(struct gridbox *gboxes, unsigned short size, unsigned char width);

extern int printwnd(struct window *wnd);
extern int isvalwnd(struct window *wnd);

#endif /* WINDOW_H */
