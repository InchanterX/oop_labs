#include <iostream>
#include "lab1/str_ops.h"

bool is_init(const char* line) {
    if (!line) {
        std::cout << "First enter a line to do operations with it" << std::endl;
        return false;
    }
    return true;
}

void init_err(void) {
    std::cout << "First enter a line to do operations with it" << std::endl;
}

int main() {
    const std::size_t max_size = 1024;
    char* line = new char[max_size];
    for (;;) {
        std::cout << "Choose one command from the list to execute:" << std::endl;
        std::cout << "1. Input string" << std::endl;
        std::cout << "2. Print" << std::endl;
        std::cout << "3. Length" << std::endl;
        std::cout << "4. Copy to buffer and print" << std::endl;
        std::cout << "5. Copy part" << std::endl;
        std::cout << "6. Comapre" << std::endl;
        std::cout << "7. Exit" << std::endl;

        int command = 0;
        if (!(std::cin >> command)) {
            std::cin.clear();
        }
        std::cout << command << std::endl;

        bool status = false;
        bool exit = false;
        int8_t pos = 0;
        int8_t len = 0;

        switch (command) {
            case 1:
            std::cout << "Enter a string:" << std::endl;
                if (std::cin.getline(line, max_size)) {
                    std::cout << "Invalid input, try enter smth. Brooo, literally anything!";
                    break;
                } else {
                    std::cin.clear();
                }
                break;
            case 2:
                status = is_init(line);
                if (!status) {
                    std::cout << "First enter a line to do operations with it" << std::endl;
                } else {
                    lab01::str_print(line);
                }
                break;
            case 3:
                status = is_init(line);
                if (!status) {
                    std::cout << "First enter a line to do operations with it" << std::endl;
                } else {
                    lab01::str_len(line);
                }
                break;
            case 4:
                status = is_init(line);
                if (!status) {
                    std::cout << "First enter a line to do operations with it" << std::endl;
                } else {
                    static std::size_t copy_size = lab01::str_len(line + 1);
                    char* copy = new char[copy_size];
                    lab01::str_copy(copy, line);
                    lab01::str_print(copy);
                }
                break;
            case 5:
                status = is_init(line);
                if (!status) {
                    std::cout << "First enter a line to do operations with it" << std::endl;
                } else {
                    std::cout << "Enter position: " << std::endl;
                    if (getline(std::cin, pos)) {
                        std::cout << "Invalid input, enter a number!";
                        break;
                    } else {
                        std::cin.clear();
                    }
                    std::cout << "Enter length: " << std::endl;
                    if (getline(std::cin, len)) {
                        std::cout << "Invalid input, enter a number!";
                        break;
                    } else {
                        std::cin.clear();
                    }
                    char* part = lab01::str_substr(line, pos, len);
                    lab01::str_print(part);
                    lab01::str_delete(part);
                }
                break;
            case 6:
                status = is_init(line);
                if (!status) {
                    std::cout << "First enter a line to do operations with it" << std::endl;
                } else {
                    char* for_comparison = new char[max_size];
                    std::cout << "Enter a string to compare:" << std::endl;
                    if (std::cin.getline(for_comparison, max_size)) {
                        std::cout << "Invalid input, try enter smth. Brooo, literally anything!";
                        break;
                    } else {
                        std::cin.clear();
                    }
                    int8_t result = lab01::str_compare(for_comparison, line);
                    if (result < 1) {
                        std::cout << "Entered string is grater than yours." << std::endl;
                    } else if (result > 1) {
                        std::cout << "Entered string is lesser than yours." << std::endl;
                    } else {
                        std::cout << "Strings are equal." << std::endl;
                    }
                    lab01::str_delete(for_comparison);
                }
                break;
            case 7:
                exit = true;
                break;
            default:
                std::cout << "Invalid input, write a number from 1 to 7." << std::endl;
                break;
        }

        if (exit) {
            break;
        }
    }

    return 0;
}