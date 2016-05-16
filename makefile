##############MAKEFILE##############

#####VARIABLES#####
#Compiler
CC=gcc -std=c99 -c

#Flags
CFLAGS=-Wall -std=c99
MAINFLAGS=-lm -lconio 

#Source files
SRC=$(wildcard *.c)

#Object files
OBJ=$(SRC:.c=.o)

#Libraries
INCLUDE=$(wildcard include/*.h)


#####MAKE#####
all: $(OBJ)

snake.o: snake.c
	@echo ==================
	@echo Compiling $@
	@echo ==================
	@echo 
	@$(CC) -o $@ -c $< $(CFLAGS) $(MAINFLAGS) 
	@echo Ta tranquilo, ta compilado.
	@echo 

%.o: %.c
	@echo ==================
	@echo Compiling $@
	@echo ==================
	@echo 
	@$(CC) -o $@ -c $< $(CFLAGS) 
	@echo Ta tranquilo, ta compilado.
	@echo 
	
.PHONY: clean 

clean:
	@rm -rf $(OBJ)
