#include "./mod/memory.h"

#include <stdio.h>

void memory_test0(void){
	char *str = 0;
	char *str2 = 0;
	printf("%lu\n", diff_sp());
	str = balloc(5);
	str[0] = 'l';
	str[1] = 'm';
	str[2] = 'a';
	str[3] = 'o';
	str[4] = '\0';
	printf("%lu\n", diff_sp());
	printf("%s\n", str);
	str2 = balloc(5);
	str2[0] = '1';
	str2[1] = '3';
	str2[2] = '2';
	str2[3] = '0';
	str2[4] = '\0';
	printf("%lu\n", diff_sp());
	printf("%s\n", str2);
	return;
}
