// logger.cpp
#include "../include/logger.h"

// Logs a message with a given priority.
// If the priority is lower than the base priority, the message is ignored (-1 is returned).
// Otherwise, the message is added to the logging queue, and 1 is returned.
ssize_t Logger::log(const std::string& message, int priority) {
    if (priority < priorityBase) {
        return -1; // Ignore messages with insufficient priority.
    } else {
        if (priority == 4) { 
            // Special case: priority 4 is downgraded to the base priority.
            priority = priorityBase;
        }
        std::lock_guard<std::mutex> lock(mtx); // Thread-safe access to the logging queue.
        logQueue.push({message, priority});    // Add the message to the queue.
        cv.notify_one();                       // Notify the writer thread.
        return 1;                              // Indicate success.
    }
}

// Continuously writes log messages from the queue to the specified file.
// Stops only when `stopThread` is true and the queue is empty.
void Logger::writeLog() {
    std::ofstream file(fileName, std::ios::app); // Open the log file in append mode.
    if (!file.is_open()) {
        // Handle file opening errors.
        std::cerr << "Error: Unable to open file " << fileName << "\n";
        return;
    }

    // Main loop for processing log messages.
    while (!stopThread || !logQueue.empty()) {
        std::unique_lock<std::mutex> lock(mtx); // Lock for safe access to the queue.
        // Wait until there's a message in the queue or `stopThread` is true.
        cv.wait(lock, [this] { return !logQueue.empty() || stopThread; });

        if (!logQueue.empty()) {
            // Extract the next message and its priority.
            auto [message, priority] = logQueue.front();
            logQueue.pop();

            // Get the current time as a formatted string.
            std::time_t now = std::time(nullptr);
            char timeStr[20];
            std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

            // Convert the priority to a string representation.
            const char* priorityStr = priorityToString(priority);

            // Write the log entry to the file.
            file << "[" << timeStr << "][" << priorityStr << "] " << message << "\n";
        }
    }
}

// Resets the base priority for logging.
// Returns 1 on success if the priority is within the valid range (0–2).
// Otherwise, returns -1 to indicate failure.
ssize_t Logger::resetPriority(int priority) {
    if (priority >= 0 && priority <= 2) {
        priorityBase = priority; // Update the base priority.
        return 1;               // Indicate success.
    }
    return -1;                  // Invalid priority value.
}

// Converts a numerical priority value to its string representation.
// Returns "Low", "Medium", "High", or "Unknown" for unrecognized values.
const char* Logger::priorityToString(int priority) const {
    switch (priority) {
        case 0: return "Low";
        case 1: return "Medium";
        case 2: return "High";
        default: return "Unknown";
    }
}
