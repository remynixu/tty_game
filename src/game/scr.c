#include "scr.h"
#include "util.h"
#include <stdio.h>
#include <limits.h>

/* COLOR */

uint8_t mkcolor(int attr, uint8_t fg, uint8_t bg){
	return (attr << 6) | (fg << 3) | bg;
}

uint8_t frcolor(uint8_t color, int how){
	switch(how){
	case COLOR_ATTR:
		return GETFIELD(color, 2, 6);
	case COLOR_FG:
		return GETFIELD(color, 3, 3);
	case COLOR_BG:
		return GETFIELD(color, 3, 0);
	default:
		break;
	}
	return ERROR(uint8_t);
}

int put_ansi_color(uint8_t code){
	int ret = code;
	if(print_raw("\033[") == EOF){
		ret = EOF;
		goto out;
	}
	if(print_raw(itoa(code, 10)) == EOF){
		ret = EOF;
		goto out;
	}
	if(putc('m', stdin) == EOF){
		ret = EOF;
		goto out;
	}
out:
	return ret;
}

int putcolor(uint8_t color){
	if(put_ansi_color(frcolor(color, COLOR_ATTR)) == EOF)
		return EOF;
	if(put_ansi_color(frcolor(color, COLOR_FG)) == EOF)
		return EOF;
	if(put_ansi_color(frcolor(color, COLOR_BG)) == EOF)
		return EOF;
	return color;
}

/* ENTRY */

uint16_t mketr(int attr, uint8_t fg, uint8_t bg, char c){
	return ((uint16_t)mkcolor(attr, fg, bg) << 8) | (uint16_t)c;
}

uint8_t fretr(uint16_t etr, int how){
	switch(how){
	case ETR_COLOR:
		return GETFIELD(etr, 8, 8);
	case ETR_CHAR:
		return GETFIELD(etr, 8, 0);
	default:
		break;
	}
	return ERROR(uint8_t);
}

int putetr(uint16_t etr){
	if(putcolor(fretr(etr, ETR_COLOR)) == EOF)
		return EOF;
	if(putc(fretr(etr, ETR_CHAR), stdin) == EOF)
		return EOF;
	return etr;
}

int printetr(uint16_t *etr, size_t sz){
	int i = 0;
	if(sz > INT_MAX)
		sz = INT_MAX;
	for(; i < (int)sz; i++){
		if(putetr(etr[i]) == EOF){
			i = -i;
			break;
		}
	}
	return i;
}

/* SCREEN */

static uint16_t screen[SCRSIZE] = {0};

void fillscr(uint16_t etr){
	for(int i = 0; i < SCRSIZE; i++)
		screen[i] = etr;
}

void clearscr(void){
	fillscr(mketr(0, COLOR_RED, COLOR_BLACK, '?'));
}

void scrput(uint16_t etr, uint8_t x, uint8_t y){
	screen[XYWTOI(x, y, SCRWIDTH)] = etr;
}

uint16_t scrget(uint8_t x, uint8_t y){
	return screen[XYWTOI(x, y, SCRWIDTH)];
}

int nextline(void){
	int ret = 0;
	if(put_ansi_color(0) == EOF){
		ret = EOF;
		goto out;
	}
	if(putc('\n', stdin) == EOF){
		ret = EOF;
		goto out;
	}
out:
	return ret;
}

int putscr(void){
	int ret = 0;
	for(int y = SCRHEIGHT - 1, tmp; y > -1; y--){
		tmp = printetr(screen + y * SCRWIDTH, SCRWIDTH);
		if(tmp < 0){
			ret = -ret + tmp;
			break;
		}
		ret += tmp;
		if(nextline() == EOF){
			ret = -ret;
			break;
		}
	}
	return ret;
}
