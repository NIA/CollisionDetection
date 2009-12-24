#include "main.h"

TEST(NilTest, ReturnsNilTest)
{
    EXPECT_EQ( 0, nil() ) << "it should return 0";
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}