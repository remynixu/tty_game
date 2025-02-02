#include "./gridbox.h"
#include "./color.h"
#include "./misc.h"

#include <stdio.h>

int isvalgbox(struct gridbox *gbox){
	if(gbox == NULL || isvalcolor(gbox->color) == 0 || gbox->icon == '\0'){
		return 0;
	}
	return 1;
}

int fput_gridbox(FILE *fstream, struct gridbox *gbox){
	int retval = 0;
	if(isfstream(fstream) == 0){
		retval = 1;
		goto out;
	}
	if(isvalgbox(gbox) == 0){
		retval = 2;
		goto out;
	}
	retval = fput_color(fstream, gbox->color);
	if(retval != 0){
		retval = 3;
		goto out;
	}
	if(fputc(gbox->icon, fstream) == EOF){
		retval = EOF;
		goto out;
	}
out:
	return retval;
}
