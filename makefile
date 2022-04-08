.DEFAULT_TARGET := $(TARGET)

SRC_DIR		= src
BIN_DIR 	= bin
SHADER_DIR	= shader

TARGET = $(BIN_DIR)/orbitsgl

CC		= gcc
LIBS	= `pkg-config --static --libs glew sdl2 cglm`
CFLAGS	= -I$(SRC_DIR) -Wall

SRC = $(shell find $(SRC_DIR) -name *.c)
OBJ = $(SRC:%.c=%.o)

$(TARGET): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -r $(BIN_DIR)
	-rm */*.o
