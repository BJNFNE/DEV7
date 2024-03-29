# Makefile LoaderMDO compilable over nmake
# nmake release compiles the release exe
# nmake debug compiles the debug exe including debug symbols

# Compiler and linker
CC = cl
LINK = link

# Compiler and linker flags for release mode
CFLAGS_RELEASE = /O2 /EHsc /MT
LDFLAGS_RELEASE = 

# Compiler and linker flags for debug mode
CFLAGS_DEBUG = /Zi /EHsc /MDd /MTd
LDFLAGS_DEBUG = /DEBUG /PDB:LoaderMDO.pdb /MAP /SUBSYSTEM:WINDOWS

# Source files
SRCS = LoaderMDO.cpp

# Object files
OBJS = $(SRCS:.cpp=.obj)

# Target executables
TARGET_RELEASE = LoaderMDO_Release.exe
TARGET_DEBUG = LoaderMDO_Debug.exe

# Default target
all: release

# Build rule for release mode
release: $(TARGET_RELEASE)

$(TARGET_RELEASE): $(OBJS)
    $(LINK) $(LDFLAGS_RELEASE) $(OBJS) /OUT:$(TARGET_RELEASE) user32.lib

# Build rule for debug mode
debug: $(TARGET_DEBUG)

$(TARGET_DEBUG): $(OBJS)
    $(LINK) $(LDFLAGS_DEBUG) $(OBJS) /OUT:$(TARGET_DEBUG) user32.lib

.cpp.obj:
    $(CC) $(CFLAGS_RELEASE) /c $<

# Clean rule
clean:
    del $(OBJS) $(TARGET_RELEASE) $(TARGET_DEBUG) LoaderMDO.pdb LoaderMDO.map
