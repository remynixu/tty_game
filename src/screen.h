#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

/* Make symbol */
char mksym(char c);

enum color{
	CLRBLK = 0,
	CLRRED,
	CLRGRN,
	CLRYLW,
	CLRBLU,
	CLRPUR,
	CLRCYN,
	CLRWHT
};

/* Make color info */
uint8_t mkci(enum color sym, enum color bg);

/* To make an icon manually:
 * struct icon test = {
 *     mksym('&'),
 *     mkci(CLRCYN, CLRBLK),
 *     1
 * };
 */
struct icon{
	char symbol;
	uint8_t color_info;
	uint8_t glow;
};

/* Make an icon */
#define mkico(c, sym, bg, glow)	\
	(struct icon){	\
		mksym(c),	\
		mkci(sym, bg),	\
		glow	\
	}

#define SCRWIDTH	30
#define SCRHEIGHT	(SCRWIDTH / 2)
#define SCRSIZE	(SCRWIDTH * SCRHEIGHT)

/* put screen */
int putscr(void);

/* fill screen */
void fillscr(struct icon ico);

#define DEFICO	mkico('?', CLRWHT, CLRBLK, 0)

/* clear screen */
void clearscr(void);

/* put on screen */
void scrput(struct icon ico, uint8_t x,
		uint8_t y);
/* get from screen */
struct icon scrget(uint8_t x, uint8_t y);

/* To make a window:
 * struct icon buf[3 * 4] = {0};
 * struct window test = {
 *     buf,
 *     // Width and height.
 *     3,
 *     4,
 *     // Position on screen.
 *     5,
 *     5
 * };
 */
struct window{
	struct icon *buf;
	uint8_t width;
	uint8_t height;
	uint8_t x;
	uint8_t y;
};

/* Make a window */
#define stackonly_mkwnd(name, ico,	\
		w, h, x, y)	\
	struct icon name##_buf[(w) * (h)];	\
	struct window name = {	\
		name##_buf,	\
		(w),	\
		(h),	\
		(x),	\
		(y)	\
	};	\
	fillwnd(&name, ico)


/* Put window */
void putwnd(struct window *wnd);
/* Put on window */
void fillwnd(struct window *wnd,
		struct icon ico);
void wndput(struct window *wnd,
		struct icon ico, uint8_t x,
		uint8_t y);
/* Get from window */
struct icon wndget(struct window *wnd,
		uint8_t x, uint8_t y);

#endif
