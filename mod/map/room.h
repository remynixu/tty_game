#ifndef ROOM_H
#define ROOM_H		1

#include "./element.h"

struct room{
	unsigned long width;
	unsigned long height;
	struct element *elements;
};

extern int mk_room(struct room *room);

#endif
