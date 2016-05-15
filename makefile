##############MAKEFILE##############

#####VARIABLES#####
#Compiler
CC=gcc

#Flags
CFLAGS=-Wall -std=c99
MAINFLAGS=-lm -lconio -Iinclude

#Source files
SRC=src/$(wildcard *.c)

#Object files
OBJ=$(SRC:.c=.o)

#Libraries
INCLUDE=include/$(wildcard *.h)

#Executable name
EXEC=snake


#####MAKE#####
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

snake.o: snake.c
	$(CC) -o $@ -c $< $(CFLAGS) $(MAINFLAGS)
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
.PHONY: clean 

clean:
	@rm -rf $(OBJ)
