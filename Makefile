CC = gcc
CFLAGS = -g -Wall -Wextra -Wpedantic -Wvla -Wfloat-equal -std=c11
LDFLAGS = -lm

SRC_DIR = src
CHIP8_DIR = $(SRC_DIR)/chip8
BUILD_DIR = build
BIN_DIR = bin

SRC_FILES = $(wildcard $(CHIP8_DIR)/*.c) $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

TARGET = $(BIN_DIR)/chip8

.PHONY: all clean

all: $(BUILD_DIR) $(BIN_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/chip8

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(TARGET) $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(TARGET)
