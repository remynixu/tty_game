#include "./clr.h"
#include "./io.h"

#include "../lib/def.h"

uint8_t mkclr(enum clr_id fg, enum clr_id bg){
	return (fg << 4) | bg;
}

uint8_t putclr(uint8_t clr){
	char escstr[] = "\033[30m";
	escstr[3] = (clr >> 4) + '0';
	if(printb(escstr) == IO_ERR)
		return IO_ERR;
	escstr[2]++;
	escstr[3] = (clr & 0x0f) + '0';
	if(printb(escstr) == IO_ERR)
		return IO_ERR;
	return clr;
}
