#include "./color.h"
#include "./output.h"

unsigned char mkclr(unsigned char fg, unsigned char bg){
	return (fg > CID_WHITE ? INVALCLR : fg << 4) |
		(bg > CID_WHITE ? INVALCLR : bg);
}

#define CLRSTRLEN	6

int putclr(unsigned char clr){
	register int printedb;
	/* no need for more memory */
	char clrstr[CLRSTRLEN] = "\033[30m";
	if(clr == INVALCLR){
		return O_ERR;
	}
	clrstr[3] = (clr >> 4) + '0';
	printedb = printb(clrstr);
	if(printedb == O_ERR){
		return O_ERR;
	}
	clrstr[2] = '4';
	clrstr[3] = (clr & 0x0f) + '0';
	printedb += printb(clrstr);
	return (printedb == CLRSTRLEN * 2 ? printedb :
		O_ERR);
}
