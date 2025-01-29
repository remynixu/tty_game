BIN = GAME
CC = gcc
CFLAGS = -std=c89 -Wpedantic -Wall -g

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
