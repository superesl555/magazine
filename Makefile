# Define compilers and flags
CXX = g++           # C++ compiler (g++).
CC = gcc            # C compiler (gcc).
CXXFLAGS = -std=c++17 -fPIC -shared  # C++ compilation flags: C++17 standard, position-independent code, and shared library.
CFLAGS = -o         # Compiler flags for output file name.
LDFLAGS = -ldl      # Linker flags to link with the dynamic loading library (libdl).

# Define file names
LIBRARY = liblogger.so         # Name of the shared library to create.
SOURCES = magazine/src/logger.cpp magazine/src/interface.cpp  # List of source files for the library.
OBJECTS = $(SOURCES:.cpp=.o)  # Object files derived from the source files.

# Default target
all: $(LIBRARY) test_program  # Default target that builds the library and the test program.

# Rule to create the shared library
$(LIBRARY): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to create the executable test program
test_program: main.c
	$(CC) $(CFLAGS) $@ $< $(LDFLAGS)

# Rule to compile .cpp files into .o object files
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Rule to clean up compiled files
clean:
	rm -f $(OBJECTS) $(LIBRARY) test_program
