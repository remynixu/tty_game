#ifndef ELEMENT_H
#define ELEMENT_H	1

enum element_icon{
	EI_FLOOR_DEFAULT = ' ',
	EI_BARREL = 'O',
	/*
	 * Wall would just be an inversed color.
	 */
	EI_WALL = ' ',
	EI_SPIKE = '^'
};

struct element{
	enum element_icon icon;
};

#endif
