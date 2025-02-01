#include "./element.h"

static struct color color_arr[EID_MAX] = {
	{CATTR_RESET, CID_WHITE, CID_BLACK},
	{CATTR_RESET, CID_BLACK, CID_WHITE},
	{CATTR_RESET, CID_YELLOW, CID_BLACK}
};

static struct gridbox gbox_arr[EID_MAX] = {
	{&color_arr[EID_FLOOR], ' '},
	{&color_arr[EID_WALL], ' '},
	{&color_arr[EID_BOX], '#'}
};

static struct physical_stat phystat_arr[EID_MAX] = {
	{0, 0, 0, 0}, /* spooky 0_0 */
	{-1, -1, -1, -1},
	{30, 2, 1, 1}
};

int isvaleid(enum element_id id){
	if(id < 0 || id > EID_MAX){
		return 0;
	}
	return 1;
}

int isvalelement(struct element *e){
	if(e == NULL || isvaleid(e->id) == 0 ||
		isvalgbox(e->gbox) == 0 || isvalphystat(e->stat) == 0){
		return 0;
	}
	return 1;
}

int mk_element(struct element *element, enum element_id id){
	int retval = 0;
	if(isvalelement(element) == 0){
		retval = 1;
		goto out;
	}
	if(isvaleid(id) == 0){
		retval = 2;
		goto out;
	}
	element->id = id;
	element->gbox = &gbox_arr[id];
	element->stat = &phystat_arr[id];
out:
	return 0;
}
