#include "./mod/display/icon.h"
#include "./mod/display/graphic.h"
#include "./mod/display/color.h"

#define ENTRY_NAME	main
#define WNDWIDTH	40
#define WNDHEIGHT	20
#define WNDSIZE		(WNDWIDTH * WNDHEIGHT)

int ENTRY_NAME(void){
	puticon(mkicon(INVALCLR, INVALGB));
	return 0;
}
