CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -g -Iinclude -w
CXXFLAGS = -Wall -Wextra -g -Iinclude -w
LDFLAGS = -lcrypto -lstdc++

SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/app


SRC_C = $(wildcard $(SRC_DIR)/*.c)
SRC_CPP = $(wildcard $(SRC_DIR)/*.cpp)
SRC = $(SRC_C) $(SRC_CPP)


OBJ_C = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_C))
OBJ_CPP = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_CPP))
OBJ = $(OBJ_C) $(OBJ_CPP)

.PHONY: all clean run run-args

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(BUILD_DIR)
	$(CXX) -o $(TARGET) $(OBJ) $(LDFLAGS)


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	cd $(BUILD_DIR) && ./app

run-args: $(TARGET)
	cd $(BUILD_DIR) && ./app $(ARGS)

clean:
	rm -rf $(BUILD_DIR)