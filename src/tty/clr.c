#include "./clr.h"
#include "./out.h"

unsigned char mkclr(enum clr_id fg,
		enum clr_id bg){
	return (fg << 4) | bg;
}

int putclr(unsigned char clr){
	char str[] = "\033[30m";
	str[3] = (clr >> 4) + '0';
	if(printb(str) == OUT_ERR){
		return -1;
	}
	str[2] = '4';
	str[3] = (clr & 0x0f) + '0';
	if(printb(str) == OUT_ERR){
		return -1;
	}
	return 0;
}
