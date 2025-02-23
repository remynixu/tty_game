#include "./wnd.h"
#include "../tty/clr.h"
#include "../tty/out.h"

#include <string.h>

/*
#define NLOG
*/
#include "../lib/debug.h"

#define WNDWIDTH	40
#define WNDHEIGHT	20
#define WNDSIZE 	(WNDWIDTH * WNDHEIGHT)

static char icons_table[8][WNDSIZE];
static unsigned char clrs_table[8][WNDSIZE];
static struct wnd wndtable[8];
static unsigned char bitmap = 0;

static unsigned short wgetpos(unsigned char x,
		unsigned char y){
	logmsg("wgetpos: %i\n",
		x + (WNDWIDTH * y));
	return x + (WNDWIDTH * y);
}

void wndclear(struct wnd *wnd){
	logmsg("wndclear called\n", 0);
	memset(wnd->icons, ' ', WNDSIZE);
	memset(wnd->clrs, mkclr(CID_WHITE,
		CID_BLACK), WNDSIZE);
}

/*
 * how about we just make an "allocator" and
 * leave the rest up to user?
 *
 * we dont use malloc, we dont need the huge
 * amount of memory heap offers, but if youre up
 * for it, refactor this to use that.
 */
struct wnd *wndalloc(void){
	unsigned char bitmap_i = 0;
	logmsg("wndalloc called\n", 0);
	while(bitmap & (1 << bitmap_i)){
		if(bitmap_i >= 8){
			return 0;
		}
		bitmap_i++;
	}
	wndtable[bitmap_i].icons =
		icons_table[bitmap_i];
	wndtable[bitmap_i].clrs =
		clrs_table[bitmap_i];
	wndclear(&wndtable[bitmap_i]);
	bitmap |= 1 << bitmap_i;
	return &wndtable[bitmap_i];
}

/*
 * you should change this if you want to port
 * this function.
 */
void wndfree(struct wnd *wnd){
	unsigned char wnd_i = 0;
	logmsg("wndfree called\n", 0);
	while(wnd != &wndtable[wnd_i]){
		if(wnd_i >= 8){
			return;
		}
		wnd_i++;
	}
	bitmap &= ~(1 << wnd_i);
	wndclear(wnd);
	wnd->icons = 0;
	wnd->clrs = 0;
	wnd = 0;
}

/*
 * why a double while loop?
 *
 * it makes an accurate representation of
 * window-to-characters on screen.
 *
 * so, instead of characters being rendered like
 * (0, 0), (1, -1), it will be like (0, 0),
 * (1, 1), like a sane math graph.
 *
 * why while loops?
 *
 * C89/90.
 */
void putwnd(struct wnd *wnd){
	unsigned char x = 0;
	unsigned char y = WNDHEIGHT;
	logmsg("putwnd called\n", 0);
	while(y > 0){
		if(x % WNDWIDTH == 0){
			putb('\n');
		}
		while(x < WNDWIDTH){
			putclr(wnd->clrs
				[wgetpos(x, y)]);
			putb(wnd->icons
				[wgetpos(x, y)]);
			x++;
		}
		x = 0;
		y--;
	}
}

void wputc(struct wnd *wnd, char c,
		unsigned char x,
		unsigned char y){
	logmsg("wputc called\n", 0);
	wnd->icons[wgetpos(x, y)] = c;
	assert(wnd->icons[wgetpos(x, y)] == c);
}

void wputclr(struct wnd *wnd, unsigned char clr,
		unsigned char x,
		unsigned char y){
	logmsg("wputclr called\n", 0);
	wnd->clrs[wgetpos(x, y)] = clr;
	assert(wnd->clrs[wgetpos(x, y)] == clr);
}
