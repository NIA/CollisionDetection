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
    EXPECT_EQ( A1, result );
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
    EXPECT_EQ( A1, result );
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
    EXPECT_EQ( A1, result );
}

// Segment and plane tests

TEST(SegmentAndPlaneTest, Parallel)
{
    Point A(1, 1, 1);
    Point B(3, 1, 1);

    Point P0(0, 0, 0);
    Vector N(0, 0, 1);
    
    Point result;

    EXPECT_FALSE( segment_and_plane_collision( A, B, P0, N, result ) );
}

TEST(SegmentAndPlaneTest, PerpendicularTrivial)
{
    Point A(1, 1, 1);  // upper than plane
    Point B(1, 1, 0);  // on the plane
    Point C(1, 1, -1); // lower
    Point D(1, 1, -2); // lower

    Point P0(0, 0, 0);
    Vector N(0, 0, 1);

    Point result;

    EXPECT_TRUE(  segment_and_plane_collision( A, B, P0, N, result ) );
    EXPECT_EQ( B, result );
    EXPECT_TRUE(  segment_and_plane_collision( A, C, P0, N, result ) );
    EXPECT_EQ( B, result );
    EXPECT_TRUE(  segment_and_plane_collision( B, C, P0, N, result ) );
    EXPECT_EQ( B, result );
    EXPECT_FALSE( segment_and_plane_collision( C, D, P0, N, result ) );
}

TEST(SegmentAndPlaneTest, Arbitrary)
{
    Point A(0,  1, -2); // line, going through B(1, 0, 0)
    Point B(1,  0,  0);
    Point C(2, -1,  2);
    Point D(4, -3,  6);

    Point P0(0, 1, 0); // simplex
    Vector N(1, 1, 1);

    Point result;

    EXPECT_TRUE( segment_and_plane_collision( A, B, P0, N, result ) );
    EXPECT_EQ( B, result );
    EXPECT_TRUE( segment_and_plane_collision( B, C, P0, N, result ) );
    EXPECT_EQ( B, result );
    EXPECT_TRUE( segment_and_plane_collision( A, D, P0, N, result ) );
    EXPECT_EQ( B, result );
    EXPECT_FALSE( segment_and_plane_collision( C, D, P0, N, result ) );
}

// Sphere and plane tests

TEST(SphereAndPlaneTest, Parallel)
{
    Point A(1, 1, 1);
    Point B(3, 1, 1);

    Point P0(0, 0, 0);
    Vector N(0, 0, 1);
    
    Point result;

    EXPECT_FALSE( sphere_and_plane_collision( A, B, 0.5, P0, N, result ) );
    EXPECT_FALSE( sphere_and_plane_collision( A, B, 1.0, P0, N, result ) );
    EXPECT_FALSE( sphere_and_plane_collision( A, B, 1.5, P0, N, result ) );
}

TEST(SphereAndPlaneTest, PerpendicularTrivial)
{
    double R = 0.25;

    Point A(1, 1, 1);   // upper than plane
    Point AA(1, 1, R);  // sphere is touching the plane, upper
    Point B(1, 1, 0);   // on the plane
    Point CC(1, 1, -R); // sphere is touching the plane, lower
    Point C(1, 1, -1);  // lower
    Point D(1, 1, -2);  // lower

    Point P0(0, 0, 0);
    Vector N(0, 0, 1);

    Point result;

    EXPECT_FALSE( sphere_and_plane_collision( C, D, R, P0, N, result ) );

    EXPECT_TRUE( sphere_and_plane_collision( A, AA, R, P0, N, result ) );
    EXPECT_EQ( B, result );
    EXPECT_FALSE( sphere_and_plane_collision( AA, A, R, P0, N, result ) );

    EXPECT_TRUE( sphere_and_plane_collision( A, B, R, P0, N, result ) );
    EXPECT_EQ( B, result );
    EXPECT_FALSE( sphere_and_plane_collision( B, A, R, P0, N, result ) );

    EXPECT_TRUE( sphere_and_plane_collision( A, CC, R, P0, N, result ) );
    EXPECT_EQ( B, result );
    EXPECT_TRUE( sphere_and_plane_collision( CC, A, R, P0, N, result ) );
    EXPECT_EQ( B, result );

    EXPECT_TRUE( sphere_and_plane_collision( D, A, R, P0, N, result ) );
    EXPECT_EQ( B, result );
    EXPECT_TRUE( sphere_and_plane_collision( A, D, R, P0, N, result ) );
    EXPECT_EQ( B, result );
}

TEST(SphereAndPlaneTest, Arbitrary)
{
    Point A(0,  1, -2); // line, going through B(1, 0, 0)
    Point B(1,  0,  0); // (going up from under the plane)
    Point C(2, -1,  2);
    Point D(4, -3,  6);
    Vector L(1, -1, 2);

    Point P0(0, 1, 0); // simplex
    Vector N(1, 1, 1);

    N.normalize();

    double R = 0.1;
    double t = ( R - (B - P0)*N )/( L*N );
    Point AA(1 - t, t, -2*t);  // touching the plane, lower
    Point CC(1 + t, -t,  2*t); // touching the plane, upper

    Point T1 = AA + R*N; // lower touch point
    Point T2 = CC - R*N; // upper touch point

    Point result;

    EXPECT_FALSE( sphere_and_plane_collision( C, D, R, P0, N, result ) );
    
    EXPECT_TRUE( sphere_and_plane_collision( A, AA, R, P0, N, result ) );
    EXPECT_EQ( T1, result );
    EXPECT_FALSE( sphere_and_plane_collision( AA, A, R, P0, N, result ) );
    
    EXPECT_TRUE( sphere_and_plane_collision( A, B, R, P0, N, result ) );
    EXPECT_EQ( T1, result );
    EXPECT_FALSE( sphere_and_plane_collision( B, A, R, P0, N, result ) );

    EXPECT_TRUE( sphere_and_plane_collision( A, CC, R, P0, N, result ) );
    EXPECT_EQ( T1, result );
    EXPECT_TRUE( sphere_and_plane_collision( CC, A, R, P0, N, result ) );
    EXPECT_EQ( T2, result );

    EXPECT_TRUE( sphere_and_plane_collision( A, D, R, P0, N, result ) );
    EXPECT_EQ( T1, result );
    EXPECT_TRUE( sphere_and_plane_collision( D, A, R, P0, N, result ) );
    EXPECT_EQ( T2, result );
}
