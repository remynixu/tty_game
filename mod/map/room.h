#ifndef ROOM_H
#define ROOM_H		1

#include "elements.h"

struct room{
	/*
	 * Unlike window.h, room has larger limit!
	 *
	 * This makes it so that we can have huge
	 * rooms but only be able to display what
	 * window.h allows.
	 * 
	 * But this isn't to say that room depends
	 * on window.h... That's not the case!
	 */
	unsigned long width;
	unsigned long height;
};

#endif
