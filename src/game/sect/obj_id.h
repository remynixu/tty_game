#ifndef OBJ_ID_H
#define OBJ_ID_H

#include "../wnd.h"

#define MAXOBJID	2

enum obj_id{
	OBJID_EMPTY,
	OBJID_WALL
};

extern void wputobjid(struct wnd *wnd,
		enum obj_id id, unsigned char x,
		unsigned char y);

#endif /* OBJ_ID_H */
