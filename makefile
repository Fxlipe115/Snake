##############MAKEFILE##############

#####VARIABLES#####
#Compiler
LINKER=gcc -o

#Object files
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

#Libraries
#INCLUDE=$(wildcard include/*.h)

#Executable name
EXEC=snake


#####MAKE#####
all: $(EXEC)

$(EXEC): $(OBJ)
	@echo ==================
	@echo Linking $@
	@echo ==================
	@echo 
	@$(LINKER) $@ $^
	@echo Ta tranquilo, ta linkado
	@echo 

$(OBJ): $(SRC)
	@cd src; make
	
.PHONY: clean 

clean:
	@rm -rf $(OBJ)
	@echo $(OBJ) removed.
