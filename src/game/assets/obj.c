#include "./obj.h"
#include "../../tty/scrbuf.h"
#include "../../tty/clr.h"

static struct{
	uint16_t sbpos[OBJSETMAX];
	uint8_t objid[OBJSETMAX];
}objfn_table;

static uint8_t objfn_cntr = 0;

static struct objset default_objset = {
	{
		' ',
		'#'
	},
	{
		(CID_WHITE << 4) | CID_BLACK,
		(CID_WHITE << 4) | CID_BLACK
	},
	{
		0,
		0
	}
};

struct objset *objset = &default_objset;

void sbputobj(struct obj obj){
	sbputclr(objset->clrs[obj.id], tosbpos(
			obj.x, obj.y));
	sbputc(objset->icons[obj.id], tosbpos(
			obj.x, obj.y));
	if(objset->fn[obj.id] == 0)
		return;
	objfn_table.sbpos[objfn_cntr] = tosbpos(
			obj.x, obj.y);
	objfn_table.objid[objfn_cntr] = obj.id;
	objfn_cntr++;
}

void sbclrobjs(void){
	int i = 0;
	objfn_cntr = 0;
	objset = &default_objset;
	while(i < OBJSETMAX){
		objfn_table.sbpos[i] = 0;
		objfn_table.objid[i] = 0;
		i++;
	}
	clrsb();
}

void *actsbpos(uint16_t sbpos, void *arg){
	int i = 0;
	while(i < OBJSETMAX)
		if(objfn_table.sbpos[i++] ==
				sbpos)
			break;
	if(i >= OBJSETMAX)
		return 0;
	return objset->fn[objfn_table.objid[i]](
			arg);
}
