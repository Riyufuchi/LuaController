# Makefile

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11

# Directories
SRC_DIR = src/code
INC_DIR = src/inc
BUILD_DIR = build
LIB_DIR = lib

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Library
LIB_NAME = libmylibrary.a
LIB_TARGET = $(BUILD_DIR)/$(LIB_NAME)

# Targets
all: $(LIB_TARGET)

$(LIB_TARGET): $(OBJ_FILES)
	ar rcs $@ $^

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(LIB_TARGET)

.PHONY: all clean

