#include "./gridbox.h"

int isvalgbox(struct gridbox gbox){
	if(isvalclr(gbox.packed_clr) == 0 || gbox.icon == 0){
		return 0;
	}
	return 1;
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
