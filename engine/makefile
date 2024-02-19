CXX = g++
# Compiler

# Directories
HEADERS_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./build
LIB_DIR = ./lib/linux
STATIC_DIR = ./static

# Source/Object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
# Compiler flags

STATIC = $(wildcard $(STATIC_DIR)/*.a)
DYNAMIC = -l$(LIB_DIR) -lGL -lglfw -lGLEW -lassimp
CXXFLAGS = -Wall -Wextra -I. -std=c++17  -fPIC

# Executable
TARGET = libOdysseyEngine.so

# Main rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJ_FILES) $(STATIC)
	$(CXX) -shared $(CXXFLAGS) $^ -o $@

# Compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create obj directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean 
