# Default to using GCC
CC = gcc
CXX = g++

# Compiler flags
RELEASE_CFLAGS = -O2 -pipe
DEBUG_CFLAGS = -g -pipe

RELEASE_CXXFLAGS = $(RELEASE_CFLAGS) -std=c++20
DEBUG_CXXFLAGS = $(DEBUG_CFLAGS) -std=c++20

# Directory containing source files
SRC_DIR = tools

# Source files (which should be not compiled)
SRCS_C = $(filter-out $(SRC_DIR)/LoaderMDO/%.c, $(shell find $(SRC_DIR) -name '*.c'))
SRCS_CPP = $(filter-out $(SRC_DIR)/LoaderMDO/%.cpp, $(shell find $(SRC_DIR) -name '*.cpp'))

# Object files
OBJS_C = $(patsubst $(SRC_DIR)/%.c,binaries/%.o,$(SRCS_C))
OBJS_CPP = $(patsubst $(SRC_DIR)/%.cpp,binaries/%.o,$(SRCS_CPP))

# Executables
TARGETS_C = $(patsubst $(SRC_DIR)/%.c,binaries/%,$(SRCS_C))
TARGETS_CPP = $(patsubst $(SRC_DIR)/%.cpp,binaries/%,$(SRCS_CPP))

# Default rule
all: release

# Release target
release: CFLAGS = $(RELEASE_CFLAGS)
release: CXXFLAGS = $(RELEASE_CXXFLAGS)
release: $(TARGETS_C) $(TARGETS_CPP)

# Debug target
debug: CFLAGS = $(DEBUG_CFLAGS)
debug: CXXFLAGS = $(DEBUG_CXXFLAGS)
debug: $(TARGETS_C) $(TARGETS_CPP)

# Rule to compile each C source file to object file
binaries/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "-------------------------------------------------------------"
	@echo "|                   Compiling C $(basename $<)               |"
	@echo "-------------------------------------------------------------"
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo

# Rule to compile each C++ source file to object file
binaries/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	@echo "-------------------------------------------------------------"
	@echo "|                 Compiling C++ $(basename $<)              |"
	@echo "-------------------------------------------------------------"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@echo

# Rule to build each C program
$(TARGETS_C): binaries/%: binaries/%.o
	@$(CC) $(CFLAGS) -o $@ $^

# Rule to build each C++ program
$(TARGETS_CPP): binaries/%: binaries/%.o
	@$(CXX) $(CXXFLAGS) -o $@ $^

# Clean rule
clean:
	@rm -f $(OBJS_C) $(OBJS_CPP)
	@rm -rf binaries
	@echo "Cleanup is done"

# Rule to use Clang
clang: CC = clang
clang: CXX = clang++
clang: release

# Rule to use Clang for debug
clang_debug: CC = clang
clang_debug: CXX = clang++
clang_debug: debug

recompile:
	make clean
	make
