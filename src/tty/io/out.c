#include "./out.h"
#include <stdio.h>

char putb(char byte){
	return (char)putchar((char)byte);
}

char printb(char *str){
	char *str_snapshot = str;
	if(str == 0){
		goto out;
	}
	while(*str != 0){
		if(putchar(*str) == EOF){
			goto out;
		}
		if((str - str_snapshot) == 0xff){
			break;
		}
		str++;
	}
out:
	return (char)(str - str_snapshot);
}
