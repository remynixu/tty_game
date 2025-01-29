#include "misc.h"

#include <stdio.h>

unsigned long capnum(unsigned long num, unsigned long cap){
	if(num > cap){
		return cap;
	}
	return num;
}

int isfstream(FILE *f){
	if(f == stdin || f == stdout || f == stderr){
		return 1;
	}
	return 0;
}
