#ifndef OBJ_H
#define OBJ_H

#include "../../lib/def.h"
#include "../../tty/wnd.h"

struct obj{
	uint8_t type; /* fn or norm */
	uint8_t id;
	uint8_t x;
	uint8_t y;
};

#define OBJCONF_FNMAX	32
#define OBJCONF_TXTRMAX	256

struct objconf{
	char icons[OBJCONF_TXTRMAX];
	char clrs[OBJCONF_TXTRMAX];
	char (*fn[OBJCONF_FNMAX])(char in);
	char fn_errcode[OBJCONF_FNMAX];
	uint8_t wid;
};

extern struct objconf *objconf;

extern void renderobj(struct obj obj);
extern char actobj(struct obj obj);

#endif /* OBJ_H */
