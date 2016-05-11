##############MAKEFILE##############

#VARIABLES

CC=gcc
CFLAGS=-Wall -lm -lconio -std=c99
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
#LIBS=$(wildcard *.h)
EXEC=snake

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

snake.o: snake.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
.PHONY: clean 

clean:
	@rm -rf *o
