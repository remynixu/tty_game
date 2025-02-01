BIN = GAME
CC = gcc
SUM = sum
CFLAGS = -std=c89 -Wpedantic -Wall -g

SRC = $(wildcard *.c) $(wildcard */*.c) $(wildcard */*/*.c)
OBJS = $(SRC:.c=.o)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(wildcard %.o): $(wildcard %.c)
	$(CC) $(CFLAGS) $< -o $@

run: $(BIN)
	./$<

# Windows non-supported:

$(SUM):
	cat $(shell find -name *.h) $(shell find -name *.c) > $@.txt

clean:
	rm -f $(BIN) $(OBJS) $(SUM).txt
