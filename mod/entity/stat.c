#include "./stat.h"

struct physical_stat physical_stat_none = STAT_EMPTY;
struct magic_stat magic_stat_none = STAT_EMPTY;
struct mental_stat mental_stat_none = STAT_EMPTY;

int isvalphystat(struct physical_stat *ps){
	if(ps->health == 0 || ps->defence == 0 ||
		ps->damage == 0 || ps->strength == 0){
		return 0;
	}
	return 1;
}

int isvalmagicstat(struct magic_stat *mas){
	if(mas->mana == 0 || mas->experience == 0){
		return 0;
	}
	return 1;
}

int isvalmentalstat(struct mental_stat *mes){
	if(mes->knowledge == 0 || mes->dexterity == 0){
		return 0;
	}
	return 1;
}
