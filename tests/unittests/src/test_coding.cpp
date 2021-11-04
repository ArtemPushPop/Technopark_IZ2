#include <iostream>
#include "gtest/gtest.h"


extern "C" {
#include "CodingFeatures.h"
}


class TestCodingFixture: public testing::Test{
protected:
    char str1[9] = "aaaaaaaa";
    char str2[9] = "bbbbbbbb";
};


TEST_F(TestCodingFixture, Compare){
    EXPECT_FALSE(CompareWithCoding(str1, str2, 2));
    EXPECT_TRUE(CompareWithCoding(str1, str1, 2));
    EXPECT_TRUE(CompareWithCoding(str1, str1 + 4, 2));
    EXPECT_FALSE(CompareWithCoding(str1, str1 + 8, 3));
}


TEST_F(TestCodingFixture, Copy){
    CopyWithCoding(str1, str1 + 4, 2);
    EXPECT_STREQ(str1, "aaaaaaaa");
    CopyWithCoding(str1, str2 + 4, 2);
    EXPECT_STREQ(str1, "bbaaaaaa");
    CopyWithCoding(str1, str2, 8);
    EXPECT_STREQ(str1, str2);
}
