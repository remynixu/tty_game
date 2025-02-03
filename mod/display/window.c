#include "./window.h"

int isvalwnd(struct window *wnd){
	if(wnd == 0 || wnd->gboxes == 0 || wnd->width == 0 || wnd->height == 0){
		return 0;
	}
	return 1;
}

int mkwnd(struct window *wnd){
	struct gridbox gbox_default = {0, '?'};
	int retval;
	unsigned short i = 0;
	if(isvalwnd(wnd) == 0){
		retval = 1;
		goto out;
	}
	gbox_default.clrinfo = mkclr(CATTR_CLEAR, CID_WHITE, CID_BLACK);
	while(i < wnd->width * wnd->height){
		wnd->gboxes[i] = gbox_default;
	}
	retval = 0;
out:
	return retval;
}

int fputwnd(FILE *f, struct window *wnd){
	int retval;
	int printbnum = 0;
	unsigned short i = 0;
	if(isvalwnd(wnd) == 0){
		retval = EOF;
		goto out;
	}
	while(i < wnd->width * wnd->height){
		retval = fputgbox(f, wnd->gboxes[i]);
		if(retval == EOF){
			goto out;
		}
		printbnum += retval;
	}
	retval = printbnum;
out:
	return retval;
}
