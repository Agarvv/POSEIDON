CC = gcc
CFLAGS = -Wall -Wextra -g
CFLAGS += -Iinclude
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/app

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

.PHONY: all clean run run-args

all: $(TARGET)


$(TARGET): $(OBJ)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


run: $(TARGET)
	cd $(BUILD_DIR) && ./app


run-args: $(TARGET)
	cd $(BUILD_DIR) && ./app $(ARGS)


clean:
	rm -rf $(BUILD_DIR)