#ifndef ELEMENT_H
#define ELEMENT_H	1

#include "../display/gridbox.h"
#include "../entity/stat.h"

enum element_id{
	EID_FLOOR = 0,
	EID_WALL,
	EID_BOX
};

struct element{
	enum element_id id;
	struct gridbox *gbox;
	struct physical_stat *stat;
};

extern struct element el_floor;

extern int mk_element(struct element *element, enum element_id);

#endif
