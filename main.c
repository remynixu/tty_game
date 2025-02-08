#include "./mod/display/window.h"
#include "./mod/display/gridbox.h"
#include "./mod/display/color.h"
#include "./mod/display/io.h"

#define ENTRY_NAME	main
#define WNDWIDTH	40
#define WNDHEIGHT	20
#define WNDSIZE		(WNDWIDTH * WNDHEIGHT)

int ENTRY_NAME(void){
	unsigned char clr = mkclr(CID_RED, CID_PURPLE);
	return putclr(clr);
}
