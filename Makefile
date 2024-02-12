# Makefile for DEV7 Tools

# Compiler for C++
CXX = g++

# Compiler flags
CXXFLAGS = -O2 -g -pipe -std=c++20

# Directory containing source files
SRC_DIR = tools

# Source files (which should be not compiled)
SRCS_CPP = $(filter-out $(SRC_DIR)/LoaderMDO/%.cpp, $(shell find $(SRC_DIR) -name '*.cpp'))

# Object files
OBJS_CPP = $(patsubst $(SRC_DIR)/%.cpp,binaries/%.o,$(SRCS_CPP))

# Executables
TARGETS = $(patsubst $(SRC_DIR)/%.cpp,binaries/%,$(SRCS_CPP))

# Default rule
all: $(TARGETS)

# Rule to build each program
binaries/%: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $<

# Clean rule
clean:
	rm -f $(OBJS_CPP)
	rm -rf binaries
