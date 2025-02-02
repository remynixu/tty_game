#include "./color.h"
#include "./misc.h"

#include <stdio.h>

static struct color color_clear = {CATTR_RESET, CID_WHITE, CID_BLACK};

void color_cleanup(void){
	fput_color(stdout, &color_clear);
	fput_color(stderr, &color_clear);
	return;
}

int isvalcid(enum color_id cid){
	if(cid <= CID_WHITE && cid >= CID_BLACK){
		return 1;
	}
	return 0;
}

int isvalcattr(enum color_attr cattr){
	if(cattr == CATTR_RESET || cattr == CATTR_BOLD || cattr == CATTR_INVERSE ||
		cattr == CATTR_UNDER || cattr == CATTR_STRIKE){
		return 1;
	}
	return 0;
}

int isvalcolor(struct color *color){
	if(color == NULL || isvalcattr(color->attr) == 0 ||
		isvalcid(color->fg) == 0 || isvalcid(color->bg) == 0){
		return 0;
	}
	return 1;
}

int fput_color(FILE *fstream, struct color *color){
	int retval = 0;
	char color_str[14] = "\001\033[00;30;40m\002";
	if(isfstream(fstream) == 0){
		retval = 1;
		goto out;
	}
	if(isvalcolor(color) == 0){
		retval = 2;
		goto out;
	}
	color_str[4] = color->attr;
	color_str[7] = color->fg;
	color_str[10] = color->bg;
	if(fputs(color_str, fstream) == EOF){
		retval = EOF;
		goto out;
	}
out:
	return retval;
}
