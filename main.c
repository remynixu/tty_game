#include "./mod/display/color.h"

#include <stdlib.h>

int register_cleanupfuncs(void){
	int retval = EXIT_SUCCESS;
	retval = atexit(color_cleanup);
	if(retval != EXIT_SUCCESS){
		goto out;
	}
out:
	return retval;
}

int main(void){
	int retval = EXIT_SUCCESS;
	struct color test = {CATTR_RESET, CID_RED, CID_BLACK};
	retval = register_cleanupfuncs();
	if(retval != EXIT_SUCCESS){
		goto out;
	}
out:
	return retval;
}
