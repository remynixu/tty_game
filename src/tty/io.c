#include "./io.h"
#include <stdio.h>

char putb(char c){
	if(putchar(c) == EOF)
		return IO_ERR;
	return c;
}

char printstr(char *str){
	char *strstart = str;
	while(*str != 0)
		if(putb(*str++) == IO_ERR)
			return IO_ERR;
	return (strstart - str);
}

char pollb(void){
	int b = getc(stdin);
	if(b == EOF)
		return IO_ERR;
	return b;
}
