#include "./scrbuf.h"
#include "./io.h"
#include "./clr.h"

#define SCRBUFWIDTH	40
#define SCRBUFHEIGHT	20
#define SCRBUFSIZE \
	(SCRBUFWIDTH * SCRBUFHEIGHT)

static struct{
	char icons[SCRBUFSIZE];
	uint8_t clrs[SCRBUFSIZE];
}scrbuf;

uint16_t tosbpos(uint8_t x, uint8_t y){
	return x + (SCRBUFWIDTH * y);
}

int putsbrow(uint8_t y){
	uint8_t x = 0;
	while(x < SCRBUFWIDTH){
		if(putclr(scrbuf.clrs[tosbpos(x,
				y)]) == IO_ERR)
			return IO_ERR;
		if(putb(scrbuf.icons[tosbpos(x,
				y)]) == IO_ERR)
			return IO_ERR;
		x++;
	}
	return 0;
}

int putsb(void){
	int put_y = SCRBUFHEIGHT - 1;
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
	do{
		if(putsbrow(put_y) == IO_ERR)
			return IO_ERR;
		if(putb('\n') == IO_ERR)
			return IO_ERR;
		put_y--;
	}
	while(put_y != 0);
	return 0;
}

void clrsb(void){
	int i = 0;
	while(i < SCRBUFSIZE){
		scrbuf.icons[i] = ' ';
		scrbuf.clrs[i] = mkclr(
				CID_WHITE,
				CID_BLACK);
		i++;
	}
}

void sbputc(char c, uint16_t sbpos){
	scrbuf.icons[sbpos] = c;
}

void sbputclr(uint8_t clr, uint16_t sbpos){
	scrbuf.clrs[sbpos] = clr;
}	
