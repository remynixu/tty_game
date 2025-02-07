#ifndef ANSI_H
#define ANSI_H		1

enum ansi_color{
	AC_BLACK = 0,
	AC_RED = 1,
	AC_GREEN = 2,
	AC_YELLOW = 3,
	AC_BLUE = 4,
	AC_PURPLE = 5,
	AC_CYAN = 6,
	AC_WHITE = 7
};

extern unsigned char mkansiclr(unsigned char fg, unsigned char bg);

extern int isvalansicid(unsigned char color_id);
extern int isvalansiclr(unsigned char packed_clr);
extern int putansiclr(unsigned char packed_clr);

#endif /* ANSI_H */
