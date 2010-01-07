#include "../Collisions/collisions.h"
#include <gtest/gtest.h>

using namespace Collisions;

// Point between tests

TEST(IsPointBetweenTest, OnSingleLine)
{
    // TODO: define and test behavior if points are not on single line
    Point p1(0, 0, 0);
    Point p2(1, 1, 2);
    Point p3(2, 2, 4);

    EXPECT_TRUE(  is_point_between(p2, p1, p3) );
    EXPECT_FALSE( is_point_between(p1, p2, p3) );
    EXPECT_FALSE( is_point_between(p3, p2, p1) );
    
    EXPECT_TRUE(  is_point_between(p1, p1, p2) );
    EXPECT_TRUE(  is_point_between(p2, p1, p2) );
}

// Distance between point and line tests
// TODO: tests for point on the line

TEST(DistancePointAndLineTest, Trivial)
{
    Point P(2.5, 0, 0);

    Point A(0, 0, 1.1);
    Vector L(0, 0, 11); // z axis

    Point H(0, 0, 0); // nearest point

    Point nearest;

    EXPECT_DOUBLE_EQ( 2.5, distance_between_point_and_line( P, A, L, nearest ) );
    EXPECT_EQ( H, nearest );
}

TEST(DistancePointAndLineTest, Arbitrary)
{
    Point P(0, 0, 0);

    Point A(0, 0, 1);
    Vector L(0.5, 0.5, -1); // on simplex

    Point H(1.0/3, 1.0/3, 1.0/3); // nearest point

    Point nearest;

    EXPECT_DOUBLE_EQ( 1.0/sqrt(3.0), distance_between_point_and_line( P, A, L, nearest ) );
    EXPECT_EQ( H, nearest );
}

TEST(DistancePointAndLineTest, BlackTest)
{
    Point A(0, 0, 1);
    Vector ZERO(0, 0, 0);

    Point nearest;

    EXPECT_THROW( distance_between_point_and_line( A, A, ZERO, nearest ), InvalidLineVectorError );
}

// Distance between point and line tests

TEST(DistancePointAndSegmentTest, Trivial)
{
    Point P(2.5, 0, 0);

    Point A(0, 0, 1.1);
    Point C(0, 0, 0.1);
    Point H(0, 0, 0); // nearest point
    Point B(0, 0, -1.2);

    EXPECT_DOUBLE_EQ( 2.5, distance_between_point_and_segment( P, A, B ) );
    EXPECT_DOUBLE_EQ( 2.5, distance_between_point_and_segment( P, A, H ) );
    EXPECT_DOUBLE_EQ( 2.5, distance_between_point_and_segment( P, H, B ) );
    EXPECT_DOUBLE_EQ( 2.5, distance_between_point_and_segment( P, B, C ) );
    EXPECT_DOUBLE_EQ( distance( P, C ), distance_between_point_and_segment( P, A, C ) );
}

TEST(DistancePointAndSegmentTest, Arbitrary)
{
    Point P(0, 0, 0);

    Point A(0, 0, 1);
    Point H(1.0/3, 1.0/3, 1.0/3); // nearest point
    Point C(0.5, 0.5, 0);
    Point B(1, 1, -1);

    double dst = 1.0/sqrt(3.0);

    EXPECT_DOUBLE_EQ( dst, distance_between_point_and_segment( P, A, B ) );
    EXPECT_DOUBLE_EQ( dst, distance_between_point_and_segment( P, A, H ) );
    EXPECT_DOUBLE_EQ( dst, distance_between_point_and_segment( P, H, B ) );
    EXPECT_DOUBLE_EQ( dst, distance_between_point_and_segment( P, A, C ) );
    EXPECT_DOUBLE_EQ( distance( P, C ), distance_between_point_and_segment( P, C, B ) );
}

TEST(DistancePointAndSegmentTest, BlackTest)
{
    Point A(0, 0, 1);

    EXPECT_THROW( distance_between_point_and_segment( A, A, A ), DegeneratedSegmentError );
}
