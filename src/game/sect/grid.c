#include "./grid.h"

void wputgrid(struct wnd *wnd,
		struct grid grid){
	wputc(wnd, grid.icon, grid.x, grid.y);
	wputclr(wnd, grid.clr, grid.x, grid.y);
}
