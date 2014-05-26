CC = clang++
CFLAGS = -std=c++11 -o3
LIBS = -lGL -lGLU -lglut
INC_PATH = /usr/include/GL

BUILD_DIR  := bin
SOURCE_DIR := src

OBJ :=  $(BUILD_DIR)/quanc8.o $(BUILD_DIR)/spline.o\
   	$(BUILD_DIR)/someapi.o $(BUILD_DIR)/lagrange.o\
	$(BUILD_DIR)/function.o\
   	$(BUILD_DIR)/main.o
BIN := main

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $(BUILD_DIR)/$(BIN) $(OBJ) $(LIBS)
clean:
	rm -f $(OBJ) $(BIN)
