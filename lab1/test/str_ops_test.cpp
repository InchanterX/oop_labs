#include "lab01/str_ops.hpp"

#include <gtest/gtest.h>

TEST(StrOpsTest, LengthCommon) {
    const char test_string[] = {"poop"};
    EXPECT_EQ(lab01::str_len(test_string), 4U);
}

TEST(StrOpsTest, LengthNull) {
    EXPECT_EQ(lab01::str_len(nullptr), 0U);
}

TEST(StrOpsTest, AllocationCommon) {
    char test_string[]{"poop"};
    char* new_string = lab01::str_alloc(test_string);
    ASSERT_NE(new_string, nullptr);
    EXPECT_STREQ(test_string, new_string);
    EXPECT_NE(test_string, new_string);
    test_string[0] = 'z';
    EXPECT_EQ(new_string[0], 'p');
    lab01::str_delete(new_string);
}

TEST(StrOpsTest_Fail, AllocationNull) {
    char* new_string = lab01::str_alloc(nullptr);
    EXPECT_EQ(new_string, nullptr);
}

TEST(StrOpsTest, DeleteCommon) {
    char* some_string = new char[5];
    lab01::str_delete(some_string);
    EXPECT_EQ(some_string, nullptr);
}

TEST(StrOpsTest, CopyCommon) {
    char test_string[]{"poop"};
    char copy_string[5];
    lab01::str_copy(copy_string, test_string);
    EXPECT_STREQ(test_string, copy_string);
}

TEST(StrOpsTest, CopyFromNull) {
    char test_string[]{"poop"};
    lab01::str_copy(test_string, nullptr);
    EXPECT_STREQ(test_string, "poop");
}

TEST(StrOpsTest, CopyToNull) {
    const char test_string[]{"poop"};
    lab01::str_copy(nullptr, test_string);
    SUCCEED();
}

TEST(StrOpsTest, SubStringCommon) {
    const char test_string[]{"poop"};
    char* copy_string = lab01::str_substr(test_string, 2, 2);
    EXPECT_STREQ(copy_string, "op");
    lab01::str_delete(copy_string);
}

TEST(StrOpsTest, SubStringIntervalOutOfLength) {
    const char test_string[]{"poop"};
    char* copy_string = lab01::str_substr(test_string, 2, 100);
    EXPECT_STREQ(copy_string, "op");
    lab01::str_delete(copy_string);
}

TEST(StrOpsTest_Fail, SubStringPositionOutOfLength) {
    const char test_string[]{"poop"};
    char* copy_string = lab01::str_substr(test_string, 10, 100);
    EXPECT_EQ(copy_string, nullptr);
}

TEST(StrOpsTest_Fail, SubStringEmptySource) {
    const char* copy_string = lab01::str_substr(nullptr, 10, 100);
    EXPECT_EQ(copy_string, nullptr);
}

TEST(StrOpsTest, CompareGrater) {
    const char test_string1[]{"poop"};
    const char test_string2[]{"arbuz"};
    const int result = lab01::str_compare(test_string1, test_string2);
    EXPECT_GT(result, 0);
}

TEST(StrOpsTest, CompareLesser) {
    const char test_string1[]{"arbuz"};
    const char test_string2[]{"poop"};
    const int result = lab01::str_compare(test_string1, test_string2);
    EXPECT_LT(result, 0);
}

TEST(StrOpsTest, CompareSlightlyGrater) {
    const char test_string1[]{"poopa"};
    const char test_string2[]{"poop"};
    const int result = lab01::str_compare(test_string1, test_string2);
    EXPECT_GT(result, 0);
}

TEST(StrOpsTest, CompareSlightlyLesser) {
    const char test_string1[]{"poop"};
    const char test_string2[]{"poopa"};
    const int result = lab01::str_compare(test_string1, test_string2);
    EXPECT_LT(result, 0);
}

TEST(StrOpsTest, CompareEqual) {
    const char test_string1[]{"poop"};
    const char test_string2[]{"poop"};
    const int result = lab01::str_compare(test_string1, test_string2);
    EXPECT_EQ(result, 0);
}

TEST(StrOpsTest, CompareNull) {
    const char test_string1[]{"poop"};
    const int result = lab01::str_compare(test_string1, nullptr);
    EXPECT_EQ(result, 0);
}
