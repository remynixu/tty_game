#ifndef OBJ_ATTR_H
#define OBJ_ATTR_H

enum obj_attr_id{
	OBJAID_NORMAL	= 0x00,
	OBJAID_SPECIAL	= 0x01
};

struct obj_normal{
	char hp;
	char dmg;
};

struct obj_special{
	char (*fn)(void *);
};

union obj_attr{
	struct obj_normal normal;
	struct obj_special special;
};

#endif /* OBJ_ATTR_H */
