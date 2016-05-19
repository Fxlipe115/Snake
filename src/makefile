##############MAKEFILE##############

#####VARIABLES#####
#Compiler
CC=gcc -std=c99 -c

#Flags
CFLAGS=-Wall -std=c99 -ggdb3 -I'../include'
MAINFLAGS=-lm -lconio 

#Source files
SRC=$(wildcard *.c)

#Object files
OBJ=$(SRC:.c=.o)

#Libraries
#INCLUDE=$(wildcard include/*.h)


#####MAKE#####
all: $(OBJ)

snake.o: snake.c
	@echo ==================
	@echo Compiling $@
	@echo ==================
	@$(CC) -o $@ -c $< $(CFLAGS) $(MAINFLAGS) 
	@echo -
	@echo Ta tranquilo, ta compilado.
	@echo -

%.o: %.c
	@echo ==================
	@echo Compiling $@
	@echo ==================
	@$(CC) -o $@ -c $< $(CFLAGS) 
	@echo -
	@echo Ta tranquilo, ta compilado.
	@echo -
	
.PHONY: clean 

clean:
	@rm -rf $(OBJ)
	@echo $(OBJ) removed.
