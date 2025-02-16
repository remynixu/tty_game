#ifndef OBJ_H
#define OBJ_H

#include "./obj_attr.h"

/* you are requested to use obj_id more than the actual
 * struct itself (it's fat). */

#define OBJID_MAX	2

enum obj_id{
	OBJID_NONE	= 0x00,
	OBJID_WALL	= 0x01
};

struct obj{
	char obj_attr_id;
	union obj_attr attr;
};

/* its more obvious system-wise that youre requesting an
 * object of specific quality using obj_id, instead of
 * needing a function like mkobj(id), the reason for
 * other modules for doing otherwise is to hide the
 * changeable implementation, which isnt likely here. */

extern struct obj obj_table[OBJID_MAX];

#endif /* OBJ_H */
