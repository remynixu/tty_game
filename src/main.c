#include "./game/wnd.h"

int main(void){
	struct wnd *mainwnd = wndalloc();
	wputc(mainwnd, '8', 4, 0);
	putwnd(mainwnd);
	wndfree(mainwnd);
	return 0;
}
