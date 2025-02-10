#include "./color.h"
#include "./output.h"

unsigned char mkclr(unsigned char fg, unsigned char bg){
	if(fg > CID_WHITE){
		return INVALCLR;
	}
	if(bg > CID_WHITE){
		return INVALCLR;
	}
	return (fg << 4) | bg;
}

int putclr(unsigned char clr){
	int printedb;
	int retval;
	char clrstr[6] = "\033[00m";
	if(clr == INVALCLR){
		return O_ERR;
	}
	printedb = 0;
	clrstr[2] = '3';
	clrstr[3] = (clr >> 4) + '0';
	retval = printb(clrstr);
	if(retval == O_ERR){
		return O_ERR;
	}
	printedb += retval;
	clrstr[2] = '4';
	clrstr[3] = (clr & 0x0f) + '0';
	retval = printb(clrstr);
	if(retval == O_ERR){
		return O_ERR;
	}
	printedb += retval;
	return printedb;
}
