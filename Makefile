# Makefile for DEV7 Tools

# Compiler for C
CC = gcc

# Compiler for C++
CXX = g++

# Compiler flags
CFLAGS = -O2 -g -pipe
CXXFLAGS = $(CFLAGS) -std=c++20

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
all: $(TARGETS_C) $(TARGETS_CPP)

# Rule to compile each C source file to object file
binaries/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule to compile each C++ source file to object file
binaries/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Rule to build each C program
$(TARGETS_C): binaries/%: binaries/%.o
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build each C++ program
$(TARGETS_CPP): binaries/%: binaries/%.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean rule
clean:
	rm -f $(OBJS_C) $(OBJS_CPP)
	rm -rf binaries
