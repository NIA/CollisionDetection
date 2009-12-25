#include "../Collisions/collisions.h"
#include <gtest/gtest.h>

TEST(NilTest, ReturnsNilTest)
{
    EXPECT_EQ( 0, nil() ) << "it should return 0";
}
