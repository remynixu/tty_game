#include "./gfxb.h"
#include "./clr.h"
#include "./icon.h"
#include "./io/out.h"

/* we have our own way of packing data. */

#ifndef __NOCLR

/* match the argument and sequence of clr data for
 * convenience and ease. */

static char gfxb_clrinfos[GFXBID_MAX] = {
	(CID_RED << 4) | CID_WHITE,
	(CID_BLACK << 0) | CID_BLACK
};

#endif /* __NOCLR */

/* respect the contracts. */

char putgfxb(char icon_id){
	/* there is no chance we get a negative value
	 * we expect respected interface. */
	if(putclr(mkclr(gfxb_clrinfos[icon_id] >> 4, gfxb_clrinfos[icon_id] & 0x0f)) == OUT_ERR){
		return OUT_ERR;
	}
	if(puticon(gfxb) == OUT_ERR){
		return OUT_ERR;
	}
	return 0;
}
