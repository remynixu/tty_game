#include "./clr.h"
#include "../../../tty/out.h"

char mkclr(char fg, char bg){
	return (fg << 4) | bg;
}

static char clrstr[6] = "\033[37m";

char putclr(char clr){
	clrstr[2] = '3';
	clrstr[3] = (clr >> 4) + '0';
	if(printb(clrstr) == OUT_ERR){
		return OUT_ERR;
	}
	clrstr[2] = '4';
	clrstr[3] = (clr & 0x0f) + '0';
	if(printb(clrstr) == OUT_ERR){
		return OUT_ERR;
	}
	return 0;
}
