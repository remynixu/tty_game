BIN = GAME
CC = gcc
CFLAGS = -std=c89 -Wpedantic -Wall -g
ifeq ($(OS),Windows_NT) # chatgpt moment
	RM = del /F /Q
	RMDIR = rmdir /S /Q
	NULLdEV = nul
else
	RM = rm -f
	RMDIR = rm -rfd
	NULLDEV = /dev/null
endif

SRC = $(wildcard *.c) $(wildcard */*.c) $(wildcard */*/*.c)
OBJS = $(SRC:.c=.o)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(wildcard %.o): $(wildcard %.c)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(BIN) $(OBJS)

run: $(BIN)
	./$<
