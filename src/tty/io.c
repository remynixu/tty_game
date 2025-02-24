#include "./io.h"
#include <stdio.h>

int putb(char c){
	int b = putchar(c);
	if(b == EOF)
		return IO_ERR;
	return b;
}

int printb(char *str){
	char *strstart = str;
	while(*str != 0)
		if(putb(*str++) == IO_ERR)
			return IO_ERR;
	return (str - strstart);
}

char pollb(void){
	int b = getc(stdin);
	if(b == EOF)
		return IO_ERR;
	return b;
}
