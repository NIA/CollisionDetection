#include "../Collisions/collisions.h"
#include <gtest/gtest.h>

// Line and plane tests

TEST(LineAndPlaneTest, Parallel)
{
    Point A(1, 1, 1);
    Vector L(1, 0, 0);

    Point P0(0, 0, 0);
    Vector N(0, 0, 1);
    
    Point result;

    EXPECT_FALSE( line_and_plane_collision( A, L, P0, N, result ) );
}

TEST(LineAndPlaneTest, PerpendicularTrivial)
{
    Point A(1, 1, 1);
    Vector L(0, 0, -2);

    Point P0(0, 0, 0);
    Vector N(0, 0, 1);

    Point A1(1, 1, 0); // projection of A
    Point result;

    EXPECT_TRUE( line_and_plane_collision( A, L, P0, N, result ) );
    EXPECT_TRUE( A1 == result );
}

TEST(LineAndPlaneTest, PerpendicularSimple)
{
    Point A(0, -0.5, 0);
    Vector L(1, 1, 0);

    Point P0(0, 1, 0);
    Vector N(1, 1, 0);

    Point A1(0.75, 0.25, 0); // projection of A
    Point result;

    EXPECT_TRUE( line_and_plane_collision( A, L, P0, N, result ) );
    EXPECT_TRUE( A1 == result );
}

TEST(LineAndPlaneTest, Arbitrary)
{
    Point A(0, 1, -2); // line, going through A1(1, 0, 0)
    Vector L(1, -1, 2);

    Point P0(0, 1, 0); // simplex
    Vector N(1, 1, 1);

    Point A1(1, 0, 0);
    Point result;

    EXPECT_TRUE( line_and_plane_collision( A, L, P0, N, result ) );
    EXPECT_TRUE( A1 == result );
}
