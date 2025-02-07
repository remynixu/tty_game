#include "./gridbox.h"
#include "./io.h"

int isvalgbox(struct gridbox gbox){
	if(isvalclr(gbox.packed_clr) == 0 || gbox.icon == 0){
		return 0;
	}
	return 1;
}

int putgbox(struct gridbox gbox){
	int retval = 0;
	int printedb = 0;
	if(isvalgbox(gbox) == 0){
		return IO_ERR;
	}
	retval = putclr(gbox.packed_clr);
	if(retval == IO_ERR){
		return IO_ERR;
	}
	printedb += retval;
	retval = putb(gbox.icon);
	if(retval == IO_ERR){
		return IO_ERR;
	}
	printedb += retval;
	return printedb;
}

struct gridbox mkgbox(char icon, unsigned char packed_clr){
	struct gridbox gbox = {0, 0};
	if(isvalclr(packed_clr) == 0 || icon == 0){
		return gbox;
	}
	gbox.icon = icon;
	gbox.packed_clr = packed_clr;
	return gbox;
}
