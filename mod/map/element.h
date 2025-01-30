#ifndef ELEMENT_H
#define ELEMENT_H	1

#include "../display/gridbox.h"
#include "stat.h"

struct element{
	struct gridbox *gbox;
	struct physical_stat *stat;
};

#endif
