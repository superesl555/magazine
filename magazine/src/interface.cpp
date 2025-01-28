// interface.cpp
#include "../include/logger.h"
// I guess this file doesn't need any comments, cout says it all
extern "C" {
    ssize_t Interface(const char* fileName, const int priority) {
        void* logger = new Logger(fileName, priority);
        if (!logger) {
            std::cerr << "Initialization failed";
            return -1;
        }
        std::cout << "Initialization was successful" << std::endl;
        while (true) {
            std::cout << "Send 1 to write a message"
                    << std::endl << "Send 2 to reset a priority" << std::endl << "Send 3 to finish" 
                    << std::endl;
            
            int choice;
            std::cin >> choice;
            if (std::cin.fail()) {
                std::cout << "Please, enter a number" << std::endl;

                std::cin.clear();

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            switch (choice) {
                case 1: {
                    std::cout << "Write your message" << std::endl;
                    std::string message;
                    std::cin.ignore();
                    std::getline(std::cin, message);
                    std::cout << "Write a priority or write -1 to use default value" << std::endl;
                    int read_priority;
                    std::cin >> read_priority;
                    if (std::cin.fail()) {
                        std::cout << "Please, enter a number" << std::endl;

                        std::cin.clear();

                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    } else {
                        ssize_t log_ans;
                        if (read_priority == -1) {
                            log_ans = static_cast<Logger*>(logger)->log(message, 4);
                        } else {
                            log_ans = static_cast<Logger*>(logger)->log(message, read_priority);
                        }

                        if (log_ans == -1) {
                            std::cerr << "This message priority lower than the base priority" << "\n";
                            break;
                        }
                        std::cout << "Message wrote successful" << std::endl;
                        break;
                    }
                }
                case 2: {
                    std::cout << "Enter a priority value" << std::endl;
                    int read_priority;
                    std::cin >> read_priority;
                    if (std::cin.fail()) {
                        std::cout << "Please, enter a number" << std::endl;

                        std::cin.clear();

                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    } else {
                        ssize_t reset_ans = static_cast<Logger*>(logger)->resetPriority(read_priority);
                        if (reset_ans == -1) {
                            std::cerr << "Uncorrect priority value" << "\n";
                        } else {
                            std::cout << "Priority was reset" << std::endl;
                        }
                    }
                    break;
                }
                case 3: {
                    delete static_cast<Logger*>(logger);
                    return 1; // leave
                }
                default:
                    std::cout << "Unknown comand" << std::endl;
                    break;
            }
        }
    }
}
