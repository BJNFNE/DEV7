# Makefile for DEV7 Tools

# Compiler for C
CC = gcc

# Compiler for C++
CXX = g++

# Compiler flags
CFLAGS = -Wall -Werror
CXXFLAGS = -Wall -Werror

# Directories containing source files
SRC_DIRS = BCD1Creator DEV7Launcher ModelPathDumper OBCViewer

# Source files
SRCS_C = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
SRCS_CPP = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))

# Object files
OBJS_C = $(SRCS_C:.c=.o)
OBJS_CPP = $(SRCS_CPP:.cpp=.o)

# Executables
TARGETS = $(patsubst %,%_program,$(SRC_DIRS))

# Default rule
all: clean_programs $(TARGETS)

# Rule to build each program
$(TARGETS): %_program : $(wildcard %/*.c) $(wildcard %/*.cpp)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile C source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile C++ source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean existing programs
clean_programs:
	rm -f $(TARGETS)

# Clean rule
clean:
	rm -f $(TARGETS) $(OBJS_C) $(OBJS_CPP)

# Rule to compile a specific program
%: $(wildcard %/*.c) $(wildcard %/*.cpp)
	$(CXX) $(CXXFLAGS) -o $@ $^
