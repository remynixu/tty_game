#include "./obj.h"

struct objconf *objconf = 0;

void renderobj(struct obj obj){
	wputc(objconf->wnd,
			objconf->icons[obj.id],
			obj.x, obj.y);
	wputclr(objconf->wnd,
			objconf->clra[obj.id],
			obj.x, obj.y);
};

// TODO
char actobj(struct obj obj,char arg){
	char res;
	if(obj.type != OBJTYPE_FN)
		return OBJ_ERR;
	res = objconf->fn[obj.id](arg);
	if(res == objconf->fn_errcode[obj.id])
		return OBJ_ERR;
	return res;
}
