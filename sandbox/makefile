# Compiler
CXX = g++
ENGINE_SO = $(addprefix $(CURDIR)/,"../engine/libOdysseyEngine.so")

# Directories
SRC_DIR = ./
OBJ_DIR = ./build

# Executable
TARGET = sandbox

# Source/Object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Compiler flags
CXX_FLAGS = -Wall -Wextra -I$(CURDIR) -std=c++17 -lGL -lglfw -lGLEW -lassimp -Wl,-rpath,'$ORIGIN' $(ENGINE_SO)

# Main rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXX_FLAGS) $^ -o $@

# Compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXX_FLAGS) -c $< -o $@

# Create obj directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean 
