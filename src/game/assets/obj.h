#ifndef OBJ_H
#define OBJ_H

#include "../../lib/def.h"

#define OBJSETMAX	(UINT8_MAX + 1)

struct objset{
	char icons[OBJSETMAX];
	uint8_t clrs[OBJSETMAX];
	void *(*fn[OBJSETMAX])(void *);
};

extern struct objset *objset;

struct obj{
	uint8_t id;
	uint8_t x;
	uint8_t y;
};

extern void sbputobj(struct obj obj);
extern void sbclrobj(void);
extern void *actsbpos(uint16_t sbpos, void *arg);

#endif /* OBJ_H */
