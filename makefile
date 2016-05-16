##############MAKEFILE##############

#####VARIABLES#####
#Compiler
LINKER=gcc -o

#Directories
SRCDIR=src

#Object files
SRC=$(wildcard $(SRCDIR)/*.c)
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
	$(LINKER) $@ $^
	@echo Ta tranquilo, ta linkado
	@echo 

$(OBJ): $(SRC)
	$(MAKE) -C $(SRCDIR) all
	
.PHONY: clean 

clean:
	@rm -rf $(OBJ)
	@echo $(OBJ) removed.
