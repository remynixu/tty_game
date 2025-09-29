#include "scr.h"

#include <stdio.h>
#include <stdint.h>
#include <errno.h>



/*
 * We will be relying on the terminal and the
 * ascii color escape codes. This is a
 * terminal game after all...
 */

int putfg(enum color_value fg){
	if(printf("\033[3%cm", fg + '0') == EOF)
		return EOF;
	return 0;
}

int putbg(enum color_value bg){
	if(printf("\033[4%cm", bg + '0') == EOF)
		return EOF;
	return 0;
}

int putg(int g){
	if(printf("\033[%cm", g + '0') == EOF)
		return EOF;
	return 0;
}

/* putchar already exists lmao */

int putetr(uint16_t etr){
	if(putg(frg(etr)) != 0)
		return -1;
	if(putfg(frfg(etr)) != 0)
		return -2;
	if(putbg(frbg(etr)) != 0)
		return -3;
	if(putchar(frc(etr)) == EOF)
		return -4;
	return 0;
}

static uint16_t scr[SCRW * SCRH] = {0};

#define xywtoi(x, y, w)	(x + y * w)
#define xytoi(x, y)	xywtoi(x, y, SCRW)

void flushscr(void){
	for(int i = 0; i < SCRW * SCRH; i++){
		scr[i] = mketr(CLRWHT, CLRBLK, 0,
				'?');
	}
}

int scrput(uint16_t etr, uint8_t x,
		uint8_t y){
	if(x >= SCRW)
		return -1;
	if(y >= SCRH)
		return -2;
	scr[xytoi(x, y)] = etr;
	return 0;
}

uint16_t scrget(uint8_t x, uint8_t y){
	if(x >= SCRW)
		return ETRERR;
	if(y >= SCRH)
		return ETRERR;
	return scr[xytoi(x, y)];
}

/*
 * Use the mechanics of putting characters in
 * the terminal and make things easier.
 */

static int putscr_row(int y){
	for(int x = 0; x < SCRW; x++){
		if(putetr(scr[xytoi(x, y)])
				!= 0){
			return -1;
		}
	}
	return 0;
}

static int putscr_nextln(void){
	if(putg(0) != 0)
		return -1;
	if(putchar('\n') == EOF)
		return -2;
	return 0;
}

int putscr(void){
	for(int y = SCRH - 1; y > -1; y--){
		if(putscr_row(y) != 0)
			return -1;
		if(putscr_nextln() != 0)
			return -2;
	}
	return 0;
}

int initsubscr(struct subscr *ss, uint8_t x,
		uint8_t y, uint8_t w, uint8_t h){
	ss->etrarr = _etralloc(w * h);
	if(!ss->etrarr)
		return -ENOMEM;
	ss->x = x;
	ss->y = y;
	ss->w = w;
	ss->h = h;
	return 0;
}

void fillsubscr(struct subscr *ss,
		uint16_t etr){
	for(int i = 0; i < ss->w * ss->h; i++)
		ss->etrarr[i] = etr;
}

void flushsubscr(struct subscr *ss){
	fillsubscr(ss, mketr(CLRWHT, CLRBLK, 0,
				'?'));
}

int subscrput(struct subscr *ss, uint16_t etr,
		uint8_t x, uint8_t y){
	if(x >= SCRW)
		return -1;
	if(y >= SCRH)
		return -2;
	ss->etrarr[xywtoi(x, y, ss->w)] = etr;
	return 0;
}

uint16_t subscrget(struct subscr *ss,
		uint8_t x, uint8_t y){
	if(x >= SCRW)
		return ETRERR;
	if(y >= SCRH)
		return ETRERR;
	return ss->etrarr[xywtoi(x, y, ss->w)];
}

static int putsubscr_row(struct subscr *ss,
		uint8_t y){
	for(int x = 0, i; x < ss->w; x++){
		if((x + ss->x) >= SCRW)
			return -1;
		i = xywtoi(x, y, ss->w);
		scrput(ss->etrarr[i], x + ss->x, y +
				ss->y);
	}
	return 0;
}

int putsubscr(struct subscr *ss){
	int retval = 0;
	for(int y = 0; y < ss->h; y++){
		if(putsubscr_row(ss, y) != 0)
			retval--;
	}
	return retval;
}
