# Makefile for DEV7 Tools

# Compiler for C
CC = gcc

# Compiler for C++
CXX = g++

# Compiler flags
CFLAGS = -Wall -Werror
CXXFLAGS = -O2 -g -pipe -std=c++20

# Directory containing source files
SRC_DIR = tools

# Source files (which should be not compiled)
SRCS_CPP = $(filter-out $(SRC_DIR)/LoaderMDO/%.cpp, $(shell find $(SRC_DIR) -name '*.cpp'))

# Object files
OBJS_C = $(SRCS_C:.c=.o)
OBJS_CPP = $(SRCS_CPP:.cpp=.o)

# Executables
TARGETS = $(patsubst %.c,%,$(SRCS_C)) $(patsubst %.cpp,%,$(SRCS_CPP))

# Directory for binaries
BIN_DIR = binaries

# Default rule
all: $(TARGETS)
	@mkdir -p $(BIN_DIR)
	@mv $(TARGETS) $(BIN_DIR)

# Rule to build each program
$(TARGETS): % : %.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $<

# Rule to compile C source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile C++ source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS_C) $(OBJS_CPP)
	rm -rf $(BIN_DIR)

