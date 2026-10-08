#include <cstddef>
#include <iostream>
#include <limits>

#include "lab01/str_ops.hpp"

namespace {

bool IsInit(const char* line) {
    if (!line) {
        std::cout << "First enter a line to do operations with it" << std::endl;
        return false;
    }
    return true;
}

void IgnoreLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

}  // namespace

int main() {
    const std::size_t kMaxSize{1024};
    char* line = nullptr;
    char input[kMaxSize]{};
    for (;;) {
        std::cout << "Choose one command from the list to execute:" << std::endl;
        std::cout << "1. Input string" << std::endl;
        std::cout << "2. Print" << std::endl;
        std::cout << "3. Length" << std::endl;
        std::cout << "4. Copy to buffer and print" << std::endl;
        std::cout << "5. Copy part" << std::endl;
        std::cout << "6. Compare" << std::endl;
        std::cout << "0. Exit" << std::endl;

        int command = 0;
        if (!(std::cin >> command)) {
            if (std::cin.eof()) {
                break;
            }
            std::cin.clear();
            IgnoreLine();
            std::cout << "Invalid input, write a number from 0 to 6." << std::endl;
            continue;
        }
        IgnoreLine();

        bool status = false;
        bool exit = false;
        std::size_t pos = 0;
        std::size_t len = 0;

        switch (command) {
            case 1:
                std::cout << "Enter a string:" << std::endl;
                if (!std::cin.getline(input, kMaxSize)) {
                    std::cout << "Invalid input, the string is too long." << std::endl;
                    std::cin.clear();
                    IgnoreLine();
                    break;
                }
                lab01::str_delete(line);
                line = lab01::str_alloc(input);
                break;
            case 2:
                status = IsInit(line);
                if (status) {
                    lab01::str_print(line);
                }
                break;
            case 3:
                status = IsInit(line);
                if (status) {
                    std::cout << lab01::str_len(line) << std::endl;
                }
                break;
            case 4:
                status = IsInit(line);
                if (status) {
                    const std::size_t copy_size = lab01::str_len(line) + 1;
                    char* copy = new char[copy_size];
                    lab01::str_copy(copy, line);
                    lab01::str_print(copy);
                    lab01::str_delete(copy);
                }
                break;
            case 5:
                status = IsInit(line);
                if (status) {
                    std::cout << "Enter position: " << std::endl;
                    if (!(std::cin >> pos)) {
                        std::cout << "Invalid input, enter a number!" << std::endl;
                        std::cin.clear();
                        IgnoreLine();
                        break;
                    }
                    IgnoreLine();
                    std::cout << "Enter length: " << std::endl;
                    if (!(std::cin >> len)) {
                        std::cout << "Invalid input, enter a number!" << std::endl;
                        std::cin.clear();
                        IgnoreLine();
                        break;
                    }
                    IgnoreLine();
                    char* part = lab01::str_substr(line, pos, len);
                    if (!part) {
                        std::cout << "Position is out of range." << std::endl;
                        break;
                    }
                    lab01::str_print(part);
                    lab01::str_delete(part);
                }
                break;
            case 6:
                status = IsInit(line);
                if (status) {
                    char* for_comparison = new char[kMaxSize];
                    std::cout << "Enter a string to compare:" << std::endl;
                    if (!std::cin.getline(for_comparison, kMaxSize)) {
                        std::cout << "Invalid input, the string is too long." << std::endl;
                        std::cin.clear();
                        IgnoreLine();
                        lab01::str_delete(for_comparison);
                        break;
                    }
                    const int result = lab01::str_compare(for_comparison, line);
                    if (result < 0) {
                        std::cout << "Entered string is less than yours." << std::endl;
                    } else if (result > 0) {
                        std::cout << "Entered string is greater than yours." << std::endl;
                    } else {
                        std::cout << "Strings are equal." << std::endl;
                    }
                    lab01::str_delete(for_comparison);
                }
                break;
            case 0:
                exit = true;
                break;
            default:
                std::cout << "Invalid input, write a number from 0 to 6." << std::endl;
                break;
        }

        std::cout << std::endl;

        if (exit) {
            break;
        }
    }

    lab01::str_delete(line);
    return 0;
}
