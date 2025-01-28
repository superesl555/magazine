// main.c
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <sys/types.h>

// Define a function pointer type for the logger function.
// It takes a file name and a priority as arguments and returns an ssize_t.
typedef ssize_t (*LoggerFunc)(const char*, char);

int main() {
    // Load the shared library `liblogger.so` dynamically.
    void* handle = dlopen("./liblogger.so", RTLD_LAZY);
    if (!handle) {
        // If the library cannot be loaded, print an error message and exit.
        fprintf(stderr, "Error loading library: %s\n", dlerror());
        return 1;
    }

    // Look up the function `Interface` in the shared library.
    LoggerFunc Interface = (LoggerFunc)dlsym(handle, "Interface");
    if (!Interface) {
        // If the function cannot be found, print an error message, close the library, and exit.
        fprintf(stderr, "Error loading function: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    // Call the `Interface` function with the file name "output.txt" and priority 1.
    ssize_t ans = Interface("output.txt", 1);
    if (ans == -1) {
        // If the function indicates failure, print an error message, close the library, and exit.
        fprintf(stderr, "Failed to create logger\n");
        dlclose(handle);
        return 1;
    }

    // Close the shared library after using it.
    dlclose(handle);

    // Indicate success to the user.
    printf("Messages logged successfully.\n");
    return 0;
}
