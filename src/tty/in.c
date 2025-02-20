#include "./in.h"

#include <stdio.h>

unsigned char pollb(void){
	int res = getc(stdin);
	return res == EOF ? IN_ERR : res;
}
