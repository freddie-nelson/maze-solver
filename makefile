#OBJS specifies which files to compile as part of the project
OBJS = main.c maze.c generators.c stack.c path.c

#CC specifies which compiler we're using
CC = clang

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = maze-solver

#This is the target that compiles our executable
all : $(OBJS) 
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
