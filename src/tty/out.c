#include "./out.h"

#include <stdio.h>

int putb(char b){
	int ret = putc(b, stdout);
	return ret == EOF ? OUT_ERR : ret;
}

int printb(char *str){
	char *strstart = str;
	while(*str){
		if(putb(*str) == OUT_ERR){
			return OUT_ERR;
		}
		str++;
	}
	return str - strstart;
}
