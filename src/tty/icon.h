#ifndef ICON_H
#define ICON_H

#define ICONID_MAX	3

/* we need guarantees throughout almost every platform
 * and architecture.
 *
 * it doesnt need to be more than a basic insert and
 * display setup. */

enum icon_id{
	ICONID_INVAL	= 0x00,
	ICONID_NONE	= 0x01,
	ICONID_WALL	= 0x02
};

extern char puticon(char id);

#endif /* ICON_H */
