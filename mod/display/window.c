#include "./window.h"
#include "./io.h"

int isvalwnd(struct window *wnd){
	if(wnd == 0 || wnd->gboxes == 0 || wnd->width == 0 || wnd->height == 0){
		return 0;
	}
	return 1;
}

struct window mkwnd(struct gridbox *gboxes, unsigned short size, unsigned char width){
	struct window wndinfo = {0};
	if(gboxes == 0 || size == 0 || width == 0){
		return wndinfo;
	}
	wndinfo.gboxes = gboxes;
	wndinfo.width = width;
	wndinfo.height = size / width;
	return wndinfo;
}

int printwnd(struct window *wnd){
	int retval = 0;
	int printedb = 0;
	unsigned short i = 0;
	if(isvalwnd(wnd) == 0){
		return IO_ERR;
	}
	while(i < wnd->width * wnd->height){
		if(i % wnd->width == 0){
			retval = putb('\n');
		}
		if(retval == IO_ERR){
			return IO_ERR;
		}
		printedb += retval;
		retval = putgbox(wnd->gboxes[i]);
		if(retval == IO_ERR){
			return IO_ERR;
		}
		printedb += retval;
	}
	return printedb;
}
