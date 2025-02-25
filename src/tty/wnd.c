/*
 * fan of SEBii, Delto, 8485, mental, lei,
 * svnth, Jane Remover, and blackwinterwells
 *
 * ^_<
 *
 * Shawn Wasabi hehe
 */

#include "./wnd.h"
#include "./clr.h"
#include "./io.h"

#include "../lib/string.h"

#define WNDWIDTH	40
#define WNDHEIGHT	20
#define WNDSIZE		(WNDWIDTH * WNDHEIGHT)
#define BITMAPSIZE	8

struct wnd{
	char icons[WNDSIZE];
	uint8_t clrs[WNDSIZE];
};

static struct wnd wndtable[BITMAPSIZE] = {{0}};
static uint8_t bitmap = 0;

void clearwnd(uint8_t wid){
	size_t i = 0;
	while(i < WNDSIZE){
		wndtable[wid].icons[i] = ' ';
		wndtable[wid].clrs[i] = mkclr(
				CID_WHITE,
				CID_BLACK);
		i++;
	}
}

uint8_t getwid(void){
	uint8_t bitmap_i = 0;
	while(bitmap >> bitmap_i)
		if(bitmap_i != BITMAPSIZE)
			bitmap_i++;
	if(bitmap_i == BITMAPSIZE)
		return WNDENOMEM;
	clearwnd(bitmap_i);
	bitmap &= 1 << bitmap_i;
	return bitmap_i;
}

void freewnd(uint8_t wid){
	clearwnd(wid);
	bitmap &= ~(1 << wid);
}

#define wndpos(x, y)	((x) + ((y) * WNDWIDTH))

/*
 * this fucking phone cant fit shit for fucks
 * sake
 */
char printwcol(uint8_t id, uint8_t y){
	uint8_t x = 0;
	while(x < WNDWIDTH){
		if(putclr(wndtable[id].clrs
				[wndpos(x, y)])
				== IO_ERR)
			return IO_ERR;
		if(putb(wndtable[id].icons
				[wndpos(x, y)])
				== IO_ERR)
			return IO_ERR;
		x++;
	}
	return 0;
}

char putwnd(uint8_t id){
	uint8_t y = WNDHEIGHT - 1;
	while(y < WNDHEIGHT){
		if(printwcol(id, y) == IO_ERR)
			return IO_ERR;
		if(putb('\n') == IO_ERR)
			return IO_ERR;
		y--;
	}
	return 0;
}

void wputc(uint8_t wid, char c, uint8_t x,
		uint8_t y){
	wndtable[wid].icons[wndpos(x, y)] = c;
}
