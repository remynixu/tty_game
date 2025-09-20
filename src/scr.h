#ifndef SCR_H
#define SCR_H

#include <stdint.h>



enum color_value{
	CLRBLK = 0,
	CLRRED,
	CLRGRN,
	CLRYLW,
	CLRBLU,
	CLRPUR,
	CLRCYN,
	CLRWHT
};

#define SCRWIDTH	30
#define SCRHEIGHT	15
#define SCRSIZE	(SCRWIDTH * SCRHEIGHT)

void setscrico(uint16_t ico, uint8_t x,
		uint8_t y);
void fillscr(uint16_t ico);
void clearscr(void);
uint16_t getscrico(uint8_t x, uint8_t y);
uint16_t mkscrico(enum color_value fg,
		enum color_value bg, uint8_t glw,
		char c);
int putscr(void);



struct subscr{
	uint8_t w;
	uint8_t h;
	uint8_t x;
	uint8_t y;
	uint16_t *icoarr;
};

void setsubscrico(struct subscr *subscr,
		uint16_t ico, uint8_t x, uint8_t y);
void fillsubscr(struct subscr *subscr,
		uint16_t ico);
void clearsubscr(struct subscr *subscr);
uint16_t getsubscrico(struct subscr *subscr,
		uint8_t x, uint8_t y);
int mksubscr(struct subscr *subscr, uint8_t w,
		uint8_t h, uint8_t x, uint8_t y);
void delsubscr(struct subscr *subscr);
void loadsubscr(struct subscr *subscr);



#endif
