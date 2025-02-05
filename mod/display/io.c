#include "./io.h"

int printb(char *bytes){
	int i = 0;
	while(bytes[i] != 0){
		if(putb(bytes[i]) == IO_ERR){
			return IO_ERR;
		}
	}
	return i;
}
