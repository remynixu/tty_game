#ifndef STAT_H
#define STAT_H		1

struct physical_stat{
	unsigned long health;
	unsigned long defence;
	unsigned long strength;
	unsigned long damage;
};

struct magic_stat{
	unsigned long mana;
	unsigned long experience;
};

struct mental_stat{
	unsigned long knowledge;
	unsigned long dexterity;
};

#define STAT_EMPTY	{0}

extern struct physical_stat physical_stat_none;
extern struct magic_stat magic_stat_none;
extern struct mental_stat mental_stat_none;

extern int isvalphystat(struct physical_stat *ps);
extern int isvalmagicstat(struct magic_stat *mas);
extern int isvalmentalstat(struct mental_stat *mes);

#endif
