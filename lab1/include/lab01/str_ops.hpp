#pragma once

#include <cstddef>

namespace lab01 {

/* If nullptr is given returns nullptr */
char* str_alloc(const char* src);

/* If nullptr is given consider it as a line of length 0 */
std::size_t str_len(const char* s);

/* If dst or src not given return nullptr.
dst array must be not shorter than src by contract of the function. */
void str_copy(char* dst, const char* src);

/* Allways works, if nullptr given it  just do nothing */
void str_delete(char*& s);

/* If nullptr is given doesn't print anything. */
void str_print(const char* s);

/* If nullptr is given returns nullptr.
If start position grater than line  length also return nullptr.
If given length exceeds the line size it return just as much as possible. */
char* str_substr(const char* s, std::size_t pos, std::size_t len);

/* If one or both lines are uninitialized return 0.
If lines are equal - returns 0, if first grater than second - return 1. Otherwise -1. */
int str_compare(const char* a, const char* b);

}  // namespace lab01
