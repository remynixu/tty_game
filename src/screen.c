#include "screen.h"
#include <ctype.h>
#include <stdio.h>

char mksym(char c){
	if(isgraph(c))
		return c;
	return '?';
}

static uint8_t pksym(uint8_t ci, uint8_t sym){
	return ci | (sym << 4);
}

static uint8_t upksym(uint8_t ci){
	return ci >> 4;
}

static uint8_t pkbg(uint8_t ci, uint8_t bg){
	return ci | bg;
}

static uint8_t upkbg(uint8_t ci){
	return ci & 0b00001111;
}

uint8_t mkci(enum color sym, enum color bg){
	uint8_t color_info = 0;
	color_info = pksym(color_info, sym);
	color_info = pkbg(color_info, bg);
	return color_info;
}

static char itoc(int i){
	return i + '0';
}

static int putci(uint8_t ci, uint8_t g){
	char clrstr[] = "\001\033[0;30;40m\002";
	clrstr[3] = itoc(g);
	clrstr[6] = itoc(upksym(ci));
	clrstr[9] = itoc(upkbg(ci));
	if(printf(clrstr) == EOF)
		return -1;
	return 0;
}

static int putico(struct icon ico,
		uint8_t clean){
	if(putci(ico.color_info, ico.glow) != 0)
		return -1;
	if(putchar(ico.symbol) == EOF)
		return -2;
	if(clean){
		if(putci(mkci(CLRBLK, CLRBLK), 1)
				!= 0){
				return -3;
		}
	}
	return 0;
}

static int printico(struct icon *arr,
		uint8_t len){
	uint8_t printed = 0;
	for(; printed < len; printed++, arr++){
		if(putico(*arr, printed == (len - 1))
				!= 0){
			return -printed;
		}
	}
	return 0;
}

static struct icon screen[SCRSIZE] = {0};

int putscr(void){
	int printed = 0;
	int w = SCRWIDTH;
	int tmp;
	for(int y = SCRHEIGHT - 1; y > -1; y--){
		tmp = printico(screen + y * w, w);
		if(tmp != 0){
			/* Because the printed count
			 * is negative on failure... */
			printed -= tmp;
			return -printed;
		}
		printed += w;
		if(putchar('\n') == EOF)
			return -printed;
	}
	return 0;
}

void fillscr(struct icon ico){
	for(int i = 0; i < SCRSIZE; i++)
		screen[i] = ico;
}

void clearscr(void){
	fillscr(DEFICO);
}

static int xywtoi(uint8_t x, uint8_t y,
		uint8_t w){
	return x + y * w;
}

static int xytoi(uint8_t x, uint8_t y){
	return xywtoi(x, y, SCRWIDTH);
}

void scrput(struct icon ico, uint8_t x,
		uint8_t y){
	screen[xytoi(x, y)] = ico;
}

struct icon scrget(uint8_t x, uint8_t y){
	return screen[xytoi(x, y)];
}

static void scrprint(struct icon *arr,
		uint8_t len, uint8_t x, uint8_t y){
	for(; len != 0; len--, x++, arr++){
		if(x >= SCRWIDTH)
			break;
		if(y >= SCRHEIGHT || y < 0)
			break;
		scrput(*arr, x, y);
	}
}

void putwnd(struct window *wnd){
	int off;
	for(int y = wnd->height - 1; y > -1; y--){
		off = y * wnd->width;
		scrprint(wnd->buf + off, wnd->width,
				wnd->x, wnd->y + y);
	}
}

void fillwnd(struct window *wnd,
		struct icon ico){
	int wndsz = wnd->width * wnd->height;
	for(int i = 0; i < wndsz; i++)
		wnd->buf[i] = ico;
}

void wndput(struct window *wnd,
		struct icon ico, uint8_t x,
		uint8_t y){
	wnd->buf[xywtoi(x, y, wnd->width)] = ico;
}

struct icon wndget(struct window *wnd,
		uint8_t x, uint8_t y){
	return wnd->buf[xywtoi(x, y, wnd->width)];
}
