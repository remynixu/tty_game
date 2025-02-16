#include "./obj.h"

struct obj obj_table[OBJID_MAX] = {
	{
		OBJAID_NORMAL,
		{
			0x00,
			0x00
		}
	},
	{
		OBJAID_NORMAL,
		{
			0xff,
			0xff
		}
	},
};
