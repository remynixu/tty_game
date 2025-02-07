#include "./mod/display/window.h"
#include "./mod/display/gridbox.h"
#include "./mod/display/color.h"
#include "./mod/display/io.h"

#define ENTRY_NAME	main
#define WNDWIDTH	40
#define WNDHEIGHT	20
#define WNDSIZE		(WNDWIDTH * WNDHEIGHT)

int ENTRY_NAME(void){
	struct gridbox gbox = {0};
	gbox.packed_clr = mkclr(CID_WHITE, CID_BLACK);
	gbox.icon = '?';
	putgbox(gbox);
	return 0;
}
