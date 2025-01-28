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

# Target to build the shared library
liblogger: $(LIBRARY)  # Goal to build the shared library.
	@echo "Library built successfully."

$(LIBRARY): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) -o $@ $^

# Target to build the test program
test_program: main.c
	$(CC) $(CFLAGS) $@ $< $(LDFLAGS)
	@echo "Test program built successfully."

# Rule to compile .cpp files into .o object files
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Rule to clean up compiled files
clean:
	rm -f $(OBJECTS) $(LIBRARY) test_program
	@echo "Cleaned up all compiled files."
