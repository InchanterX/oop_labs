#include <iostream>
#include <algorithm>

namespace lab01 {

    std::size_t str_len(const char* s) {
        if (!s) {
            return 0;
        }
        std::size_t len = 0;
        for (std::size_t i = 0; s[i] != '\0'; ++i) {
            len++;
        }
        return len;
    }

    char* str_alloc(const char* src) {
        if (!src) {
            return nullptr;
        }
        std::size_t len = str_len(src) + 1;
        char* new_str = new char[len];
        if (!new_str) {
            return nullptr;
        }
        for (std::size_t i = 0; i < len; ++i) {
            new_str[i] = src[i];
        }
        return new_str;
    }

    void str_delete(char*& s) {
        delete[] s;
        s = nullptr;
    }

    void str_copy(char* dst, const char* src) {
        // dst must be not shorter than src
        if (!dst || !src) {
            return;
        }
        std::size_t src_len = str_len(src) + 1;
        for (std::size_t i = 0; i < src_len; ++i) {
            dst[i] = src[i];
        }
    }


    void str_print(const char* s) {
        if (!s) return;
        for (std::size_t i = 0; s[i] != '\0'; ++i) {
            std::cout << s[i];
        }
        std::cout << '\n';
    }

    char* str_substr(const char* s, std::size_t pos, std::size_t len) {
        if (!s) {
            return nullptr;
        }
        const std::size_t s_len = str_len(s);
        if (s_len < pos) {
            return nullptr;
        }

        const std::size_t target_size = std::min(s_len - pos , len);
        char* result = new char[target_size + 1];
        for (std::size_t i = pos, j = 0; j < target_size; ++i, ++j) {
            result[j] = s[i];
        }
        result[target_size] = '\0';
        return result;
    }

    int str_compare(const char* a, const char* b) {
        if (!a || !b) {
            return 0;
        }
        int result = 0;
        const std::size_t a_len = str_len(a);
        const std::size_t b_len = str_len(b);
        const std::size_t min_len = std::min(a_len, b_len);
        for (std::size_t i = 0; i < min_len; ++i) {
            if (a[i] == b[i]) {
                continue;
            } else if (a[i] < b[i]) {
                result = -1;
                break;
            } else {
                result = 1;
                break;
            }
        }
        if (result == 0 && a_len > b_len) {
            result = 1;
        } else if (result == 0 && a_len < b_len) {
            result = -1;
        }
        return result;
    }
}