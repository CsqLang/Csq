# Define the compiler, flags, and libraries
CXX := g++

# More flags should be enabled slowly
# For now I recommend looking at:
# -Wall -Wextra -pedantic
# The flags are found in this Stackoverflow answer "https://stackoverflow.com/questions/5088460/f"

# Define directories and files
SRC_DIR := . AST Builtin Parser Runtime Tokenizer include
INC_DIR := AST Builtin Grammar Parser Runtime Tokenizer include
OBJ_DIR := ./
BIN := csq
HOME := ${HOME}
BIN_DIR := $(HOME)/.local/bin
INCLUDE_DIR := $(HOME)/.local/include/csq
USER_SHELL := ${SHELL}
DOC := _doc.py

# List of source files
SRC := $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.cpp))
PY_SRC := $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.py))
OBJ := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

# Check if the target is 'dev'
ifeq ($(filter dev,$(MAKECMDGOALS)),dev)
	CXXFLAGS := -std=c++17 -Wall -Wextra
else
	CXXFLAGS := -std=c++17
endif

# Default rule
.PHONY: all
.DELETE_ON_ERROR:
all: $(OBJ_DIR) $(BIN)

# Rule to link the executable
$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to create the build directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

dev: $(BIN)

# Format the python code
.PHONY: format
format: $(PY_SRC)
	@python -m black $^
	@python -m isort $^
	@python $(DOC)


# Install to the ~/.local/ directory
# Use the build.sh script to do the PATh and Include stuff
install: $(BIN) $(INCLUDE_DIR) $(BIN_DIR)
	@cp $(BIN) $(BIN_DIR)
	@cp -r $(INC_DIR) $(INCLUDE_DIR)
	@$(USER_SHELL) build.sh

uninstall: $(INCLUDE_DIR) $(BIN_DIR)
	@rm -r $(OBJ) $(BIN) $(INCLUDE_DIR) $(BIN_DIR)

$(BIN_DIR):
	@mkdir -p $@

$(INCLUDE_DIR):
	@mkdir -p $@

# Rule to clean build artifacts
.PHONY: clean
clean:
	@rm $(OBJ) $(BIN)
