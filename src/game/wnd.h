#ifndef WND_H
#define WND_H

/*
 * - note: no default window like ncurses
 *   because it introduces implicitness.
 */
struct wnd{
	char *icons;
	unsigned char *clrs;
};

/*
 * where would the window come from?
 * here!
 */

/*
 * - allocates a clear window.
 * return
 * - success: allocated window
 * - fail: 0
 */
extern struct wnd *wndalloc(void);

/*
 * - frees a window.
 */
extern void wndfree(struct wnd *wnd);

/*
 * - "zeroes out" a window.
 */
extern void wndclear(struct wnd *wnd);

/*
 * - puts a window on screen.
 */
extern void putwnd(struct wnd *wnd);

/*
 * - puts a character on a window, positions
 *   specified with x and y.
 */
extern void wputc(struct wnd *wnd, char c,
		unsigned char x,
		unsigned char y);

/*
 * - puts a color on a window, like wputc().
 */
extern void wputclr(struct wnd *wnd,
		unsigned char clr,
		unsigned char x,
		unsigned char y);

#endif /* WND_H */
