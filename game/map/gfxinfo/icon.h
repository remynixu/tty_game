#ifndef ICON_H
#define ICON_H

/* it doesnt need to be more than a basic insert and
 * display setup. */

enum icon_id{
	IID_INVAL	= '?',
	IID_NONE	= ' ',
	IID_WALL	= '#'
};

/* puts an icon on terminal, returns 0 on success,
 * OUT_ERR on failure. */

extern char puticon(char icon);

#endif /* ICON_H */
