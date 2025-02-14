#ifndef OBJ_H
#define OBJ_H

enum obj_id{
	OID_NULL = 0x00,
	OID_WALL = 0x01
};

struct obj{
#ifndef __NOCLR
	char clr;
#endif /* __NOCLR */
	char icon;
	char id;
};

extern struct obj mkobj(struct gfxb gfxb, char id);

#endif /* OBJ_H */
