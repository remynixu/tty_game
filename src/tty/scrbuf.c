#include "./scrbuf.h"
#include "./io.h"
#include "./clr.h"

#define SCRBUFWIDTH	40
#define SCRBUFHEIGHT	20
#define SCRBUFSIZE \
	(SCRBUFWIDTH * SCRBUFHEIGHT)

struct scrbuf{
	char icons[SCRBUFSIZE];
	uint8_t clrs[SCRBUFSIZE];
};

static struct scrbuf scrbuf;

void clrscrbuf(void){
	int i = 0;
	while(i < SCRBUFSIZE){
		scrbuf.icons[i] = ' ';
		scrbuf.clrs[i] = mkclr(
				CID_WHITE,
				CID_BLACK);
		i++;
	}
}

int wndpos(uint8_t x, uint8_t y){
	return x + (SCRBUFWIDTH * y);
}

int putscrbufrow(uint8_t y){
	uint8_t x = 0;
	while(x < SCRBUFWIDTH){
		if(putclr(scrbuf.clrs[wndpos(x,
				y)]) == IO_ERR)
			return IO_ERR;
		if(putb(scrbuf.icons[wndpos(x,
				y)]) == IO_ERR)
			return IO_ERR;
		x++;
	}
	return 0;
}

int putscrbuf(void){
	int put_y = SCRBUFHEIGHT;
	/*
	 * Thu. Feb. 07, 2025
	 *
	 * weird logic but we have to print the
	 * rows in bottom to top form so that it
	 * "behaves" like a graph.
	 *
	 * instead of seeing:	we see likewise:
	 *
	 * +-----		|
	 * |			|
	 * |			+-----
	 *
	 */
	while(put_y <= SCRBUFHEIGHT){
		if(putscrbufrow(put_y) == IO_ERR)
			return IO_ERR;
		if(putb('\n') == IO_ERR)
			return IO_ERR;
		put_y--;
	}
	return 0;
}
