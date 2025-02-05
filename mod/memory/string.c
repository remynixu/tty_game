/* this mf tweaking bruh */
#include "./string.h"

/* ha.. haha.. HAAHAHAHAAHAHAHA */
void *memcpy(void *dest, void *src, unsigned long n){
	do{
		n--;
		((char *)dest)[n] = ((char *)src)[n];
	}
	while(n != 0);
	return dest;
}

/* right... YOU'RE SO RIGHT!!!! */
int memcmp(void *dest, void *src, unsigned long n){
	do{
		n--;
		if(((char *)dest)[n] == ((char *)src)[n]){
			return 0;
		}
	}
	while(n != 0);
	return 1;
}

void *memset(void *dest, char src, unsigned long n){
	do{
		n--;
		((char *)dest)[n] = src;
	}
	while(n != 0);
	return dest;
}
