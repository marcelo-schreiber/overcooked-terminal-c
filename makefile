PROJ_NAME=overcooked
 
# .c files
C_SOURCE=$(wildcard ./src/*.c)
 
# .h files
H_SOURCE=$(wildcard ./include/*.h)
 
# Object files
OBJ=$(subst .c,.o,$(subst src,objects,$(C_SOURCE)))
 
# Compiler and linker
CC=gcc
 
# Flags for compiler
CC_FLAGS=-c         \
         -Wall      \
				 -finput-charset=UTF-8
 
LIB_FLAGS=-lm\
					 -lpthread\

# Command used at clean target
RM = rm -rf
 
# Compilation and linking
all: objFolder $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	$(CC) $^ -o $@ $(LIB_FLAGS) 
 
./objects/%.o: ./src/%.c ./include/%.h
	$(CC) $< $(CC_FLAGS) -o $@ $(LIB_FLAGS)
 
./objects/main.o: ./src/main.c $(H_SOURCE)
	$(CC) $< $(CC_FLAGS) -o $@ $(LIB_FLAGS)
 
objFolder:
	@mkdir -p objects
 
clean:
	$(RM) ./objects/*.o $(PROJ_NAME) *~
 
.PHONY: all clean