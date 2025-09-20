#include "scr.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>



/*
 * We need an easy way to store, change, and
 * use colors.
 *
 * A color (clr) is made up of:
 * - foreground (fg)
 * - background (bg)
 */

static uint8_t setclrfg(uint8_t clr,
		enum color_value fg){
	return clr | ((uint8_t)fg << 4);
}

static uint8_t setclrbg(uint8_t clr,
		enum color_value bg){
	return clr | (uint8_t)bg;
}

static uint8_t getclrfg(uint8_t clr){
	return clr >> 4;
}

static uint8_t getclrbg(uint8_t clr){
	return clr & 0x0f;
}

static uint8_t mkclr(enum color_value fg,
		enum color_value bg){
	uint8_t clr = 0;
	clr = setclrfg(clr, fg);
	clr = setclrbg(clr, bg);
	return clr;
}

static int putclrfg(enum color_value fg){
	if(printf("\033[3%cm", fg + '0') == EOF)
		return -1;
	return 0;
}

static int putclrbg(enum color_value bg){
	if(printf("\033[4%cm", bg + '0') == EOF)
		return -1;
	return 0;
}

static int putclr(uint8_t clr){
	if(putclrbg(getclrbg(clr)) != 0)
		return -1;
	if(putclrfg(getclrfg(clr)) != 0)
		return -2;
	return 0;
}



/*
 * We need an easy-to-port character system
 * for the icon.
 *
 * A symbol (sym) is made up of:
 * - glow (glw)
 * - character (c)
 */

static uint8_t setsymglw(uint8_t sym,
		uint8_t glw){
	return sym | (glw << 7);
}

static uint8_t setsymc(uint8_t sym, char c){
	return sym | (c & 0x7f);
}

static uint8_t getsymglw(uint8_t sym){
	return sym >> 7;
}

static uint8_t getsymc(uint8_t sym){
	return sym & 0x7f;
}

static uint8_t mksym(uint8_t glw, char c){
	uint8_t sym = 0;
	sym = setsymglw(sym, glw);
	sym = setsymc(sym, c);
	return sym;
}

static int putsymglw(uint8_t glw){
	if(printf("\033[%dm", glw) == EOF)
		return -1;
	return 0;
}

static int putsymc(char c){
	if(putchar(c) == EOF)
		return -1;
	return 0;
}

/* [ DEPRECATED ] */
static int putsym(uint8_t sym){
	if(putsymglw(getsymglw(sym)) != 0)
		return -1;
	if(putsymc(getsymc(sym)) != 0)
		return -2;
	return 0;
}



/*
 * We need a compact way to color a character
 * and display it.
 *
 * An icon (ico) is made up of:
 * - color
 * - symbol
 */

static uint16_t seticoclr(uint16_t ico,
		uint8_t clr){
	return ico | ((uint16_t)clr << 8);
}

static uint16_t seticosym(uint16_t ico,
		uint8_t sym){
	return ico | (uint16_t)sym;
}

static uint8_t geticoclr(uint16_t ico){
	return ico >> 8;
}

static uint8_t geticosym(uint16_t ico){
	return ico & 0x00ff;
}

static uint16_t mkico(uint8_t clr,
		uint8_t sym){
	uint16_t ico = 0;
	ico = seticoclr(ico, clr);
	ico = seticosym(ico, sym);
	return ico;
}

static uint16_t mkico_def(void){
	return mkico(mkclr(CLRRED, CLRBLK),
			mksym(0, '?'));
}

static int putico(uint16_t ico){
	/* I mildly dislike this hack. */
	if(putsymglw(getsymglw(geticosym(ico)))
			!= 0)
		return -1;
	if(putclr(geticoclr(ico)) != 0)
		return -2;
	if(putsymc(getsymc(geticosym(ico))) != 0)
		return -3;
	return 0;
}

static int printico(uint16_t *ico,
		uint8_t sz){
	for(; sz != 0; sz--, ico++){
		if(putico(*ico) != 0)
			return -((int)sz);
	}
	return 0;
}



/*
 * We need a way to display an array of
 * colored characters (or icons) for the user
 * to see.
 *
 * A screen (scr) is composed of an array of
 * icons with the following dimensions:
 * - SCRWIDTH
 * - SCRHEIGHT
 * - SCRSIZE
 */

/*
 * We have no intentions of supporting screen
 * sizes greater than UINT16_MAX.
 */

#if SCRWIDTH >= UINT8_MAX ||	\
				SCRHEIGHT >= UINT8_MAX
#error "SCRSIZE >= UINT16_MAX"
#endif

static uint16_t scr[SCRSIZE] = {0};

static uint16_t xywtoi(uint8_t x, uint8_t y,
		uint8_t w){
	return x + y * w;
}

static uint16_t xytoi(uint8_t x, uint8_t y){
	return xywtoi(x, y, SCRWIDTH);
}

void setscrico(uint16_t ico, uint8_t x,
		uint8_t y){
	scr[xytoi(x, y)] = ico;
}

static void setnscrico(uint16_t *ico,
		uint8_t x, uint8_t y, uint16_t sz){
	for(; sz != 0; sz--, ico++, x++){
		if(x >= SCRWIDTH)
			break;
		setscrico(*ico, x, y);
	}
}

void fillscr(uint16_t ico){
	for(uint16_t i = 0; i < SCRSIZE; i++)
		scr[i] = ico;
}

void clearscr(void){
	fillscr(mkico_def());
}

uint16_t getscrico(uint8_t x, uint8_t y){
	return scr[xytoi(x, y)];
}

uint16_t mkscrico(enum color_value fg,
		enum color_value bg, uint8_t glw,
		char c){
	return mkico(mkclr(fg, bg),
			mksym(glw, c));
}

static int nextline(void){
	if(putsym(mksym(0, '\n')) != 0)
		return -1;
	return 0;
}

int putscr(void){
	int16_t y = SCRHEIGHT - 1;
	for(; y > -1; y--){
		if(printico(scr + y * SCRWIDTH,
					SCRWIDTH) != 0)
			break;
		if(nextline() != 0)
			break;
	}
	return -y;
}



/*
 * We need a way to manipulate multiple icons
 * easily, we do this by using a subscreen
 * (subscr).
 *
 * Here are the member explanations:
 * - w is width.
 * - h is height.
 * - x is x position on screen
 * - y is y position on screen
 * - icoarr is the the icon array buffer used
 *   to store data to display to screen.
 */

void setsubscrico(struct subscr *subscr,
		uint16_t ico, uint8_t x, uint8_t y){
	subscr->icoarr[xywtoi(x, y, subscr->w)]
		= ico;
}

void fillsubscr(struct subscr *subscr,
		uint16_t ico){
	for(uint16_t i = 0; i < subscr->w *
			subscr->h; i++){
		subscr->icoarr[i] = ico;
	}
}

void clearsubscr(struct subscr *subscr){
	fillsubscr(subscr, mkico_def());
}

uint16_t getsubscrico(struct subscr *subscr,
		uint8_t x, uint8_t y){
	return subscr->icoarr[xywtoi(x, y,
			subscr->w)];
}

int mksubscr(struct subscr *subscr, uint8_t w,
		uint8_t h, uint8_t x, uint8_t y){
	subscr->w = w;
	subscr->h = h;
	subscr->x = x;
	subscr->y = y;
	subscr->icoarr = malloc(sizeof(
				*subscr->icoarr) * w * h);
	if(!subscr->icoarr)
		return -1;
	return 0;
}

void delsubscr(struct subscr *subscr){
	free(subscr->icoarr);
	subscr->w = 0;
	subscr->h = 0;
	subscr->x = 0;
	subscr->y = 0;
}

void loadsubscr(struct subscr *subscr){
	for(int y = subscr->h - 1; y > -1; y--)
		setnscrico(subscr->icoarr + y *
				subscr->w, subscr->x,
				subscr->y + y, subscr->w);
}
