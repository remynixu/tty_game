#include "./icon.h"
#include "./color.h"
#include "./graphic.h"
#include "./output.h"

struct icon mkicon(unsigned char packed_clr, char graphic_byte){
	struct icon icon;
	if(packed_clr == INVALCLR){
		packed_clr = mkclr(CID_RED, CID_WHITE);
	}
	if(graphic_byte == INVALGB){
		graphic_byte = GID_INVAL;
	}
	icon.packed_clr = packed_clr;
	icon.graphic_byte = graphic_byte;
	return icon;
}

int puticon(struct icon icon){
	int printedb = 0;
	int retval = 0;
	retval = putclr(icon.packed_clr);
	/* invalid colors arent that bad. */
	if(retval != O_ERR){
		printedb += retval;
	}
	retval = putb(icon.graphic_byte);
	if(retval == O_ERR){
		return O_ERR;
	}
	printedb += retval;
	return printedb;
}
