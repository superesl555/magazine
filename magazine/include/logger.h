// logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <ctime>
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

class Logger {
public:
    // Constructor initializes the logger with a file name and base priority.
    // It also starts the writer thread.
    Logger(const std::string& fileName, int priority) 
        : fileName(fileName), stopThread(false), priorityBase(priority) {
        writerThread = std::thread(&Logger::writeLog, this); // Start the writer thread.
    }

    // Destructor ensures proper cleanup by stopping the writer thread.
    ~Logger() {
        stopThread = true;         // Signal the writer thread to stop.
        cv.notify_all();           // Wake up the thread if it's waiting.
        writerThread.join();       // Wait for the thread to finish.
    }

    // Logs a message with a specified priority by adding it to the queue.
    ssize_t log(const std::string& message, int priority);

    // Resets the base priority for filtering log messages.
    ssize_t resetPriority(int priority);

private:
    std::string fileName;                         // Name of the file where logs are written.
    std::queue<std::pair<std::string, int>> logQueue; // Queue for storing log messages with priorities.
    std::mutex mtx;                               // Mutex for thread-safe queue operations.
    std::condition_variable cv;                   // Condition variable for synchronizing threads.
    std::thread writerThread;                     // Thread responsible for writing logs to the file.
    std::atomic<bool> stopThread;                 // Atomic flag to signal the writer thread to stop.
    int priorityBase;                             // Base priority for filtering log messages.

    // Writes log messages from the queue to the file.
    void writeLog();

    // Converts a priority integer to a corresponding string representation.
    const char* priorityToString(int priority) const;
};

#endif // LOGGER_H
