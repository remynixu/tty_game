BIN = GAME
CC = gcc
SUM = sum
CFLAGS = -std=c89 -Wpedantic -Wall -g -fno-builtin

SRC = $(wildcard *.c) $(wildcard */*.c) \
      $(wildcard */*/*.c) $(wildcard */*/*/*.c)
OBJS = $(SRC:.c=.o)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(wildcard %.o): $(wildcard %.c)
	$(CC) $(CFLAGS) $< -o $@

run: $(BIN)
	./$<

push:
	git status
	git add .
	git commit -m "auto pushed"
	git push origin main

# Windows non-supported:

$(SUM):
	cat $(shell find -name *.h) $(shell find -name *.c) > $@.txt

clean:
	rm -f $(BIN) $(OBJS) $(SUM).txt
