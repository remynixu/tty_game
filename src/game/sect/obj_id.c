#include "./obj_id.h"
#include "./grid.h"
#include "../wnd.h"
#include "../../tty/clr.h"

struct objdisp{
	char icon;
	unsigned char pckclr;
};

static struct objdisp objdisp_table[MAXOBJID] = {
	{
		' ',
		(CID_WHITE << 4) | CID_BLACK
	},
	{
		'#',
		(CID_WHITE << 4) | CID_WHITE
	}
};

void wputobjid(struct wnd *wnd, enum obj_id id,
		unsigned char x,
		unsigned char y){
	struct grid grid;
	grid.icon = objdisp_table[id].icon;
	grid.clr = mkclr(objdisp_table[id].pckclr
			>> 4, objdisp_table[id]
			.pckclr & 0x0f);
	grid.x = x;
	grid.y = y;
	wputgrid(wnd, grid);
}
