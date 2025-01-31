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

#endif
