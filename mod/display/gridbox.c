#include "./gridbox.h"
#include "./color.h"
#include "../misc.h"

#include <stdio.h>

struct gridbox gbox_empty = {&color_clear, '?'};

int isvalgbox(struct gridbox *gbox){
	if(gbox == NULL || isvalcolor(gbox->color) == 0 || gbox->icon == '\0'){
		return 1;
	}
	return 0;
}

int fput_gridbox(FILE *fstream, struct gridbox *gbox){
	int retval = 0;
	if(isfstream(fstream) == 0){
		fstream = stdout;
	}
	if(isvalgbox(gbox) == 0){
		gbox = &gbox_empty;
	}
	retval = fput_color(fstream, gbox->color);
	if(retval != 0){
		goto out;
	}
	retval = fputc(gbox->icon, fstream);
out:
	return retval;
}
