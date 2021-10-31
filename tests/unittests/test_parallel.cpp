#include <iostream>
#include "gtest/gtest.h"


extern "C" {
#include "CountSymbols.h"
}


TEST(TestCarDBFixture, DeepCopy) {
ASSERT_TRUE(1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}