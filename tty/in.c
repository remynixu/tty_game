#include "./in.h"
#include <stdio.h>

/* this is a platform dependent code section, expect
 * slight parting from tty_game standards. */

char pollb(void){
	int retval = getc(stdin);
	if(retval == EOF){
		return POLL_ERR;
	}
	return (char)retval;
}

char pollnb(char count){
	while(count != 0x00){
		if(pollb() == POLL_ERR){
			return count;
		}
		count--;
	}
	return count;
}
