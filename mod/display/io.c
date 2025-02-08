#include "./io.h"

int printb(char *bytes){
	int i = 0;
	if(bytes == 0){
		return IO_ERR;
	}
	while(bytes[i] != 0){
		if(putb(bytes[i]) == IO_ERR){
			return IO_ERR;
		}
		i++;
	}
	return i;
}
