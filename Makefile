# OS type start

ifeq ($(OS),Windows_NT)
	OS_TYPE = windows
	RUN_CMD = ${OUTPUT}$(EXE)

	EXE = .exe
	LIB_PATH = -L"./libs/SDL3/lib" -L"./libs/lua"
	LUA_FLAG = -llua54
else
	UNAME_S := $(shell uname -s)
	RUN_CMD = ./${OUTPUT}

	EXE =
	LIB_PATH =
	LUA_FLAG = -llua5.4
	ifeq ($(UNAME_S),Linux)
		OS_TYPE = linux
	else ifeq ($(UNAME_S),Darwin)
		OS_TYPE = macos
	else
		OS_TYPE = unknown
	endif
endif

# OS type end

# Variables start

CC = g++
LANG_STD = -std=c++20
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I"./include" -I"./libs" -I"./src"
SRC_FILES = ./src/*.cpp \
			./src/Game/*.cpp \
			./src/Logger/*.cpp \
			./src/Utils/*.cpp
LINKER_FLAGS = -lSDL3 -lSDL3_image -lSDL3_ttf -lSDL3_mixer $(LUA_FLAG)
OBJ_NAME = gameengine
OBJ_PATH = ./bin/
OUTPUT = ${OBJ_PATH}$(OBJ_NAME)

# Variables end

build:
	mkdir -p $(OBJ_PATH)
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) ${LIB_PATH} $(LINKER_FLAGS) -o ${OUTPUT}$(EXE)

run:
	$(RUN_CMD)

brun:
	make && make run

clean:
	rm -rf ${OBJ_PATH}