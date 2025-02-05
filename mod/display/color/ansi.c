#include "./ansi.h"
#include "../io.h"

int isvalansicid(unsigned char color_id){
	if(color_id > AC_WHITE){
		return 0;
	}
	return 1;
}

int isvalansiclr(unsigned char packed_clr){
	if(isvalansicid((packed_clr << 4) >> 4) == 0 || isvalansicid((packed_clr >> 4) << 4) == 0){
		return 0;
	}
	return 1;
}

unsigned char mkansiclr(unsigned char fg, unsigned char bg){
	unsigned char packed_clr = (fg << 4) | bg;
	if(isvalansiclr(packed_clr) == 0){
		return 0;
	}
	return packed_clr;
}

int printansiclr(unsigned char packed_clr){
	char clrstr[5] = "\033[30m";
	int retval = 0;
	int printedb = 0;
	if(isvalansiclr(packed_clr) == 0){
		return IO_ERR;
	}
	clrstr[3] = (packed_clr >> 4) + '0';
	retval = printb(clrstr);
	if(retval == IO_ERR){
		return IO_ERR;
	}
	printedb += retval;
	clrstr[2] = '4';
	clrstr[3] = ((packed_clr << 4) >> 4) + '0';
	retval = printb(clrstr);
	if(retval == IO_ERR){
		return IO_ERR;
	}
	printedb += retval;
	return printedb;
}
