#include "util.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

/* IO */

int input_raw(void){
	int in;
	do{
		in = getc(stdin);
	}
	while(in == '\n');
	return in;
}

int print_raw(char *str){
	int ret = 0;
	for(; *str != 0; str++){
		if(putc(*str, stdin) == EOF){
			ret = EOF;
			break;
		}
	}
	return ret;
}

/* STRING */

char itoc(int i){
	char c = 0;
	if(i < 0)
		i = -i;
	if(i < 10)
		c = i + '0';
	else if(i < 36)
		c = (i - 10) + 'a';
	else if(i < 62)
		c = (i - 36) + 'A';
	else
		c = '?';
	return c;
}

char *itoa(int i, int base){
	static char buf[sizeof(size_t) * 8] = {0};
	uint8_t buf_i = 0;
	if(i < 0){
		i = -i;
		*buf = '-';
		buf_i++;
	}
	for(; buf_i < sizeof(size_t) * 8 && i != 0; buf_i++){
		buf[buf_i] = itoc(i % base);
		i /= base;
	}
	buf_i--;
	for(int tmp_i = *buf == '-' ? 1 : 0; buf_i > tmp_i; buf_i--, tmp_i++)
		BITSWAP(buf[tmp_i], buf[buf_i]);
	return buf;
}
