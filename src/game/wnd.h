#ifndef WND_H
#define WND_H

struct wnd{
	char *icons;
	unsigned char *clrs;
};

/* where would the window come from?
 * here! */

/*
 * - allocates memory big enough for a window.
 * return
 * - success: allocated window
 * - fail: 0
 */
extern struct wnd *wndalloc(void);

/*
 * - puts a window on screen.
 */
extern void putwnd(struct wnd *wnd);

#endif /* WND_H */
