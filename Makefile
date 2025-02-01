COMPILER = g++
LANG_STD = -std=c++20
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I"./libs" -I"./src"
SRC_FILES = ./src/*.cpp \
			./src/Game/*.cpp \
			./src/Logger/*.cpp \
			./src/Utils/*.cpp
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3
OBJ_NAME = gameengine

build:
	$(COMPILER) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS) -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

brun:
	make && make run

clean:
	rm $(OBJ_NAME)