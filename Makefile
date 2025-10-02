# Default to using GCC
CC = gcc
CXX = g++

# Compiler flags
RELEASE_CFLAGS = -O2 -pipe
DEBUG_CFLAGS = -g -pipe
RELEASE_CXXFLAGS = $(RELEASE_CFLAGS) -std=c++23 -I.
DEBUG_CXXFLAGS = $(DEBUG_CFLAGS) -std=c++23 -I.

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
	@echo "Release builds were compiled, can be found in the binaries folder\b"

# Debug target
debug: CFLAGS = $(DEBUG_CFLAGS)
debug: CXXFLAGS = $(DEBUG_CXXFLAGS)
debug: $(TARGETS_C) $(TARGETS_CPP)
	@echo "Debug builds were compiled, can be found in the binaries folder\b"

# Rule to compile each C source file to object file
binaries/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "-------------------------------------------------------------"
	@echo "|                   Compiling C $(@D)              	|"
	@echo "-------------------------------------------------------------"
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo

# Rule to compile each C++ source file to object file
binaries/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	@echo "-------------------------------------------------------------"
	@echo "|                 Compiling C++ $(@D)			  |"
	@echo "-------------------------------------------------------------"
	@$(CXX) $(CXXFLAGS) -v -c -o $@ $<
	@echo

# Rule to build each C program
$(TARGETS_C): binaries/%: binaries/%.o
	@$(CC) $(CFLAGS) -o $@ $^

# Rule to build each C++ program
$(TARGETS_CPP): binaries/%: binaries/%.o
	@$(CXX) $(CXXFLAGS) -v -o $@ $^ -lstdc++ -lm -lc
	@if [ "$(MAKECMDGOALS)" = "debug" ]; then \
		$(CXX) $(DEBUG_CXXFLAGS) -v -o $@ $^ -Xlinker -Map=$(basename $@).map -lstdc++ -lm -lc; \
	fi

# Clean rule
clean:
	@rm -f $(OBJS_C) $(OBJS_CPP)
	@rm -rf binaries
	@rm -rf build
	@rm -rf CMakeFiles
	@echo "Cleanup is done"

.PHONY: clean all

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
	@echo "Recompilation is done"

# Define build directory
BUILD_DIR = build
# Target to run cmake and make
cmake:
	# Create build directory if it doesn't exist
	@if [ ! -d "$(BUILD_DIR)" ]; then \
		mkdir $(BUILD_DIR); \
	fi
	@cd $(BUILD_DIR) && cmake ..
	@cd $(BUILD_DIR) && make

ninja:
	# Create build directory if it doesn't exist
	@if [ ! -d "$(BUILD_DIR)" ]; then \
		mkdir $(BUILD_DIR); \
	fi
	@cmake -S . -B build -G Ninja
	@cd $(BUILD_DIR) && ninja

strip:
	@strip --strip-all $(TARGETS_C) $(TARGETS_CPP)
	@echo "Stripping is done"

