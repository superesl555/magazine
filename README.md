# Logger Library

This is a C++ library for logging messages into a file with configurable priority levels. It supports dynamic linking and can be used to record log messages with timestamps and different severity levels.


## Features

- Thread-safe: Uses mutexes and condition variables to ensure safe logging in multithreaded environments.
- File output: Logs are written to a file with timestamps and priority labels.
- Dynamic linking: The logging library is provided as a shared object, allowing dynamic loading and use in applications.


## Building the Library

To build the library, you can use the provided Makefile. The Makefile defines rules to compile the source files and create the shared library (liblogger.so), as well as an example test program (test_program) that demonstrates how to use the library.

### Dependencies
- g++: C++ compiler for building the library.
- gcc: C compiler for building the test program.
- libdl: The dynamic linking library for loading the shared library at runtime.

### Building Instructions
1. Clone this repository or download the source files.

2. Navigate to the directory containing the Makefile.

3. Run the following command to build the library and the test program: **make**
This will create the shared library *liblogger.so* and the executable *test_program*.

4. To clean up compiled files and binaries, use: **make clean**


## Using the Logger Library

### Priority Levels
The logger supports three priority levels:

- **Low**(0)
- **Medium**(1)
- **High**(2)

Messages with a priority lower than the base priority will be ignored.

### Resetting Priority
You can reset the base priority using the *Logger::resetPriority(int priority)* function. This allows you to filter out lower-priority log messages dynamically.

## License
This project is licensed under the MIT License.