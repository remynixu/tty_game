#include "./gfxb.h"
#include "./clr.h"
#include "./icon.h"
#include "../../../tty/out.h"

/* follow the interface. thats all you need.
 * (refering to clr.h and icon.h). */

struct gfxb mkgfxb(char clr, char icon){
	struct gfxb gfxb;
	gfxb.clr = clr;
	gfxb.icon = icon;
	return gfxb;
}

char putgfxb(struct gfxb gfxb){
	putclr(gfxb.clr);
	if(puticon(gfxb.icon) == OUT_ERR){
		return OUT_ERR;
	}
	return 0;
}
