#include "./element.h"

static struct color color_arr[EID_MAX] = {
	{0}, /* unused */
	{CATTR_RESET, CID_BLACK, CID_WHITE},
	{CATTR_RESET, CID_YELLOW, CID_BLACK}
};

static struct gridbox gbox_arr[EID_MAX] = {
	GBOX_EMPTY,
	{&color_arr[EID_WALL], ' '},
	{&color_arr[EID_BOX], '#'}
};

static struct physical_stat phystat_arr[EID_MAX] = {
	STAT_EMPTY,
	{-1, -1, -1, -1},
	{30, 2, 1, 1}
};

struct element el_floor = {EID_FLOOR, &gbox_arr[EID_FLOOR], &phystat_arr[EID_FLOOR]};

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
	if(isvalelement(element) == 0){
		return 1;
	}
	if(isvaleid(id) == 0){
		element = &el_floor;
		return 0;
	}
	element->id = id;
	element->gbox = &gbox_arr[id];
	element->stat = &phystat_arr[id];
	return 0;
}
