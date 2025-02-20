#include "./wnd.h"
#include "../tty/out.h"

#define WNDWIDTH	40
#define WNDHEIGHT	20
#define WNDSIZE 	(WNDWIDTH * WNDHEIGHT)

static char icons_table[8][WNDSIZE];
static unsigned char clrs_table[8][WNDSIZE];
static struct wnd wndtable[8];
static unsigned char bitmap = 0;

/*
 * how about we just make an allocator and
 * leave the rest up to user?
 */
struct wnd *wndalloc(void){
	unsigned char bitmap_i = 0;
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
	bitmap |= 1 << bitmap_i;
	return &wndtable[bitmap_i];
}

void putwnd(struct wnd *wnd){
	unsigned short disp_i = 0;
	while(disp_i < WNDSIZE){
		if(disp_i % WNDWIDTH == 0){
			putb('\n');
		}
		putclr(wnd->clrs[disp_i]);
		putb(wnd->icons[disp_i]);
		disp_i++;
	}
}
