#include "color.h"
#include "../misc.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

static struct color color_clear_def = {CATTR_RESET, CID_WHITE, CID_BLACK};
struct color *color_clear = &color_clear_def;

void color_cleanup(void){
	/*
	 * What do you even do if the functions
	 * fail here...
	 */
	fput_color(stdout, color_clear);
	fput_color(stderr, color_clear);
	/*
	 * We dont clean stdin, that's weird
	 */
	return;
}

int isvalcid(enum color_id cid){
	if(cid <= '9' && cid >= '0'){
		return 1;
	}
	return 0;
}

int isvalcattr(enum color_attr cattr){
	if(cattr == '0' || cattr == '1' || cattr == '4' ||
		cattr == '7' || cattr == '9'){
		return 1;
	}
	return 0;
}

int isvalcolor(struct color *color){
	if(color == NULL || isvalcattr(color->attr) == 0 ||
		isvalcid(color->fg) == 0 || isvalcid(color->bg) == 0){
		return 1;
	}
	return 0;
}

int fput_color(FILE *fstream, struct color *color){
	int retval = 0;
	char color_str[] = "\001\033[00;30;40m\002";
	if(isfstream(fstream) == 0){
		fstream = stdout;
	}
	if(isvalcolor(color) == 0){
		color = color_clear;
	}
	color_str[4] = color->attr;
	color_str[7] = color->fg;
	color_str[10] = color->bg;
	/*
	 * Save the EOF error if occured
	 */
	retval = fputs(color_str, fstream);
	return retval;
}
