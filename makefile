.DEFAULT_TARGET := $(TARGET)

SRC_DIR		= src
BIN_DIR 	= bin
SHADER_DIR	= shader

SHADERS 		= $(shell find $(SHADER_DIR) -name *.glsl)
SHADER_TARGETS 	= $(SHADER:$(SHADER_DIR)/%.glsl=$(BIN_DIR)/%.glsl)

TARGET = $(BIN_DIR)/osv
LAUNCH = "./launch"

CC		= gcc
LIBS	= `pkg-config --static --libs glew sdl2 cglm`
CFLAGS	= -I$(SRC_DIR) -Wall

SRC = $(shell find $(SRC_DIR) -name *.c)
OBJ = $(SRC:%.c=%.o)

_dummy := $(shell mkdir -p $(BIN_DIR))

$(TARGET): $(OBJ) shaders
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)

shaders:
	cp $(shell find $(SHADER_DIR) -wholename "$(SHADER_DIR)/*") $(BIN_DIR)

$(BIN_DIR)/%.glsl: $(SHADER_DIR)/%.glsl
	cp $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -r $(BIN_DIR)
	-rm */*.o

run: $(TARGET)
	$(LAUNCH) $(TARGET)
