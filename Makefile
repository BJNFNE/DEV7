# Makefile for compiling programs in different directories

# Compiler for C
CC = gcc

# Compiler for C++
CXX = g++

# Compiler flags
CFLAGS = -Wall -Werror
CXXFLAGS = -O2 -g -Wall -Wextra -pipe -std=c++20

# Directory containing source files
SRC_DIR = tools

# Source files (excluding LoaderMDO)
SRCS_C = $(filter-out $(SRC_DIR)/LoaderMDO/%.c, $(shell find $(SRC_DIR) -name '*.c'))
SRCS_CPP = $(filter-out $(SRC_DIR)/LoaderMDO/%.cpp, $(shell find $(SRC_DIR) -name '*.cpp'))

# Object files
OBJS_C = $(SRCS_C:.c=.o)
OBJS_CPP = $(SRCS_CPP:.cpp=.o)

# Executables
TARGETS = $(patsubst %.c,%,$(SRCS_C)) $(patsubst %.cpp,%,$(SRCS_CPP))

# Default rule
all: $(TARGETS)

# Rule to build each program
$(TARGETS): % : %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

# Rule to compile C source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile C++ source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(TARGETS) $(OBJS_C) $(OBJS_CPP)
