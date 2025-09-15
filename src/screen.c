#include "screen.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>

static struct{
	enum{
		SUCCESS = 0,
		SYMBOL_ERROR,
		IO_ERROR,
		FAILURE
	}error;
	char *string;
}screen_state = {0};

static void check_error(void){
	assert(screen_state.error == SUCCESS);
	assert(screen_state.string == 0);
}

static void set_error(int code){
	static char *string[] = {
		"SCREEN_NO_ERROR",
		"SCREEN_SYMBOL_ERROR",
		"SCREEN_IO_ERROR",
		"SCREEN_UNKNOWN_ERROR"
	};
	screen_state.error = code;
	screen_state.string = &string[code];
}

void get_error(int *code, char *string){
	code = &screen_state.error;
	string = screen_state.string;
}


struct color{
	unsigned int foreground : 4;
	unsigned int background : 4;
};

static int put_color(struct color color){
	static char *string = "\033[30;40m";
	check_error();
	string[3] = color.foreground + '0';
	string[6] = color.background + '0';
	if(printf("%s", string) == EOF){
		set_error(IO_ERROR);
		return -1;
	}
	return 0;
}


struct icon{
	unsigned int glow : 1;
	unsigned int symbol : 7;
	struct color color;
};

static int put_glow(int glow){
	static char *string = "\033[0m";
	check_error();
	string[2] = glow;
	if(printf("%s", string) == EOF){
		set_error(IO_ERROR);
		return -1;
	}
	return 0;
}

static int put_symbol(char symbol){
	check_error();
	if(!isgraph(symbol)){
		set_error(SYMBOL_ERROR);
		symbol = '?';
	}
	if(putchar(symbol) == EOF){
		set_error(IO_ERROR);
		return -1;
	}
	return 0;
}

static int put_icon(struct icon icon){
	check_error();
	if(put_glow(icon.glow) != 0)
		return -1;
	if(put_color(icon.color) != 0)
		return -2;
	if(put_symbol(icon.symbol) != 0)
		return -3;
	return 0;
}

static int print_icon(struct icon *array,
		size_t size){
	size_t count = 0;
	check_error();
	for(; count < size; count++, array++){
		if(put_icon(*array) != 0)
			break;
	}
	return count;
}


#define SCREEN_WIDTH	40
#define SCREEN_HEIGHT	20
#define SCREEN_SIZE	(SCREEN_WIDTH *	\
		SCREEN_HEIGHT)

static struct icon screen[SCREEN_SIZE] = {0};

static int set_next_row(void){
	if(put_glow(0) != 0)
		return -1;
	if(putchar('\n') == EOF){
		set_error(IO_ERROR);
		return -2;
	}
	return 0;
}

int put_screen(void){
	size_t count = 0, offset, tmp;
	for(int row = SCREEN_HEIGHT - 1; row > -1; row--){
		offset = row * SCREEN_WIDTH;
		tmp = print_icon(screen + offset,
					SCREEN_WIDTH);
		count += tmp;
		if(tmp != SCREEN_WIDTH)
			break;
		if(set_next_row() != 0)
			break;
	}
	return count;
}
