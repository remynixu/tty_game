#include "./icon.h"
#include "./color.h"
#include "./graphic.h"
#include "./output.h"

struct icon mkicon(unsigned char packed_clr, char graphic_byte){
	struct icon icon;
	icon.packed_clr = (packed_clr == INVALCLR ?
		mkclr(CID_RED, CID_WHITE) : packed_clr);
	icon.graphic_byte = (graphic_byte == INVALGB ?
		GID_INVAL : graphic_byte);
	return icon;
}

int puticon(struct icon icon){
	register int printedb;
	printedb = putclr(icon.packed_clr);
	printedb += (printedb == O_ERR ? -O_ERR : 0);
	printedb = (putb(icon.graphic_byte) == O_ERR ?
		O_ERR : printedb + 1);
	return printedb;
}
