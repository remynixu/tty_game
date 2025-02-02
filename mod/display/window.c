#include "./window.h"
#include "./misc.h"

#include <stdio.h>

int isvalwnd(struct window *wnd){
	if(wnd == NULL || wnd->gboxes == NULL || wnd->width == 0 ||
		wnd->height == 0){
		return 0;
	}
	return 1;
}

int fput_wnd(FILE *fstream, struct window *wnd){
	int retval = 0;
	unsigned short i = 0;
	if(isfstream(fstream) == 0){
		retval = 1;
		goto out;
	}
	if(isvalwnd(wnd) == 0){
		retval = 2;
		goto out;
	}
	while(i < (wnd->height * wnd->width)){
		if(i % wnd->width == 0){
			retval = fputc('\n', fstream);
		}
		if(retval == EOF){
			goto out;
		}
		retval = fput_gridbox(fstream, &wnd->gboxes[i]);
		if(retval != 0){
			goto out;
		}
		i++;
	}
out:
	return retval;
}
