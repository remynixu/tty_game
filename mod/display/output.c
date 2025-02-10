#include "./output.h"

int printb(char *str){
	register int printedb = 0;
	while(str != 0 && *str != 0){
		if(putb(*str) == O_ERR){
			return O_ERR;
		}
		printedb++;
		str++;
	}
	return printedb;
}
