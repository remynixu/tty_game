#include "./output.h"

int printb(char *str){
	int i;
	int retval;
	int printedb = 0;
	/* noone has to worry about crashing anymore
	 * with this. */
	if(str == 0){
		return O_ERR;
	}
	i = 0;
	while(str[i] != 0){
		retval = putb(str[i]);
		if(retval == O_ERR){
			return O_ERR;
		}
		printedb += retval;
		i++;
	}
	return printedb;
}
