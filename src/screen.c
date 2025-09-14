#include "screen.h"

#include <stdio.h>
#include <stddef.h>
#include <ctype.h>


struct screen_error screen_error = {0};

static char *errtostr(int error){
	static char *str[] = {
		"SUCCESS",
		"IO_ERROR",
		"BAD_SYMBOL"
	};
	return str[error];
}

static void set_error(int error){
	screen_error.code = error;
	screen_error.str = errtostr(error);
}

static struct icon screen[SCREEN_SIZE] = {0};

static char itoc(int i){
	return i + '0';
}

static int put_color(struct icon ic){
	static char str[] = "\033[0;30;40m";
	str[2] = itoc(ic.glow);
	str[5] = itoc(ic.fg);
	str[8] = itoc(ic.bg);
	if(printf("%s", str) == EOF){
		set_error(IO_ERROR);
		return -1;
	}
	return 0;
}

static int put_color_clear(void){
	if(printf("\033[0m") == EOF){
		set_error(IO_ERROR);
		return -1;
	}
	return 0;
}

static int put_symbol(char symbol){
	if(!isgraph(symbol)){
		set_error(BAD_SYMBOL);
		symbol = '?';
	}
	if(putchar(symbol) == EOF){
		set_error(IO_ERROR);
		return -1;
	}
	return 0;
}

static int put_icon(struct icon ic){
	if(put_color(ic) != 0)
		return -1;
	if(put_symbol(ic.symbol) != 0)
		return -1;
	return 0;
}

static int print_icon(struct icon *arr,
		size_t len){
	size_t i = 0;
	for(; i < len; i++, arr++){
		if(put_icon(*arr) != 0)
			break;
	}
	return i;
}


void fillscr(struct icon ic){
	for(int i = 0; i < SCREEN_SIZE; i++)
		screen[i] = ic;
}

void clearscr(void){
	static struct icon clear_icon = {
		0,
		'#',
		ICON_RED,
		ICON_BLACK
	};
	fillscr(clear_icon);
}

static int xytoi(int x, int y){
	return x + y * SCREEN_WIDTH;
}

void scrput(struct icon ic, size_t x,
		size_t y){
	screen[xytoi(x, y)] = ic;
}

struct icon scrget(size_t x, size_t y){
	return screen[xytoi(x, y)];
}

static int next_line(void){
	if(put_color_clear() != 0)
		return -1;
	if(putchar('\n') == EOF){
		set_error(IO_ERROR);
		return -1;
	}
	return 0;
}

int putscr(void){
	int off = 0;
	int fail_point = 0;
	int tmp0 = 0;
	int tmp1 = 0;
	for(int y = SCREEN_HEIGHT - 1; y > -1;
			y--){
		off = y * SCREEN_WIDTH;
		tmp0 = print_icon(screen + off,
				SCREEN_WIDTH);
		tmp1 += tmp0;
		if(tmp0 != SCREEN_WIDTH)
			goto fail;
		if(next_line() != 0)
			goto fail;
		continue;
fail:
		fail_point = tmp1;
		break;
	}
	return fail_point;
}
