#include "window.h"
#include "../misc.h"

#include <stdio.h>

int isvalwnd(struct window *wnd){
	if(wnd == NULL || wnd->gboxes == NULL || wnd->width == NULL ||
		wnd->height == NULL){
		return 0;
	}
	return 1;
}

int fput_wnd(FILE *fstream, struct window *wnd){
	int retval = 0;
	unsigned short width_i = 0;
	unsigned short height_i = 0;
	unsigned short i = 0;
	if(isfstream(fstream) == 0){
		fstream = stdin;
	}
	if(wnd == NULL){
		/*
		 * No, we aren't falling back.
		 */
		retval = EINVAL;
		goto out;
	}
	while(height_i < wnd->height){
		if(width_i == wnd->width){
			retval = fputc('\n', fstream);
			width_i = 0;
			height_i++;
		}
		if(retval != 0){
			goto out;
		}
		retval = fput_gridbox(fstream, &wnd->gbox[i]);
		if(retval != 0){
			goto out;
		}
		width_i++;
		i++;
	}
out:
	return retval;
}
