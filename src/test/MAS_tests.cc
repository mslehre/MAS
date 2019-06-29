#include <gtest/gtest.h>

namespace MAS_test {
    TEST(MAS_tests, test_test) {
        EXPECT_EQ(0,0);
    }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
