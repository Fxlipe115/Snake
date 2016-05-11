snakewindows: snake.c
	gcc -o snake.exe snake.c  -lm -lconio -Wall -std=c99
snakelinux: snake.c
	gcc -o snake snake.c -lm -Wall -std=c99
##############MAKEFILE##############

#VARIABLES

CC=gcc
CFLAGS=-Wall -lm -lconio -std=c99
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
LIBS=
EXEC=snake

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

snake.o: snake.c $(LIBS)
	$(CC) -o $@ -c $< $(CFLAGS)
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
.PHONY: clean

clean:
	@rm -rf *o
