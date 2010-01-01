#include "../Collisions/collisions.h"
#include <gtest/gtest.h>
#include <cmath>

using namespace Collisions;

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
    
    Point result1, result2;

    EXPECT_EQ( 0, sphere_and_plane_collision( A, B, 0.5, P0, N, result1, result2 ) );
    EXPECT_EQ( 0, sphere_and_plane_collision( A, B, 1.0, P0, N, result1, result2 ) );
    EXPECT_EQ( 0, sphere_and_plane_collision( A, B, 1.5, P0, N, result1, result2 ) );
}

TEST(SphereAndPlaneTest, PerpendicularTrivial)
{
    Point A(1, 1, 1);     // upper than plane
    Point AA(1, 1, 0.5);  // touching the plane, upper
    Point B(1, 1, 0);     // on the plane
    Point CC(1, 1, -0.5); // touching the plane, lower
    Point C(1, 1, -1);    // lower
    Point D(1, 1, -2);    // lower

    Point P0(0, 0, 0);
    Vector N(0, 0, 1);

    Point result1, result2;

    EXPECT_EQ( 0, sphere_and_plane_collision( C, D, 0.5, P0, N, result1, result2 ) );
    EXPECT_EQ( 1, sphere_and_plane_collision( A, AA, 0.5, P0, N, result1, result2 ) );
    EXPECT_EQ( B, result1 );
    EXPECT_EQ( 1, sphere_and_plane_collision( A, B, 0.5, P0, N, result1, result2 ) );
    EXPECT_EQ( B, result1 );
    EXPECT_EQ( 2, sphere_and_plane_collision( A, CC, 0.5, P0, N, result1, result2 ) );
    EXPECT_EQ( B, result1 );
    EXPECT_EQ( B, result2 );
    EXPECT_EQ( 2, sphere_and_plane_collision( D, A, 0.5, P0, N, result1, result2 ) );
    EXPECT_EQ( B, result1 );
    EXPECT_EQ( B, result2 );
}

inline bool pair_equal( Point &expected1, Point &expected2, Point &actual1, Point &actual2)
{
    bool res1 = ( expected1 == actual1 )&&( expected2 == actual2 );
    bool res2 =        ( expected1 == actual2 )&&( expected2 == actual1 );
    return res1 || res2;
}

TEST(SphereAndPlaneTest, Arbitrary)
{
    Point A(0,  1, -2); // line, going through B(1, 0, 0)
    Point B(1,  0,  0);
    Point C(2, -1,  2);
    Point D(4, -3,  6);
    Vector L(1, -1, 2);

    Point P0(0, 1, 0); // simplex
    Vector N(1, 1, 1);

    N = N/sqrt( N.sqared_norm() );

    double t = ( 0.5 - (B - P0)*N )/( L*N );
    Point AA(1 - t, t, -2*t);  // touching the plane, upper
    Point CC(1 + t, -t,  2*t);  // touching the plane, lower

    Point T1 = AA + N*0.5; // upper touch point
    Point T2 = CC - N*0.5; // upper touch point

    Point result1, result2;

    EXPECT_EQ( 0, sphere_and_plane_collision( C, D, 0.5, P0, N, result1, result2 ) );
    EXPECT_EQ( 1, sphere_and_plane_collision( A, AA, 0.5, P0, N, result1, result2 ) );
    EXPECT_EQ( T1, result1 );
    EXPECT_EQ( 1, sphere_and_plane_collision( A, B, 0.5, P0, N, result1, result2 ) );
    EXPECT_EQ( T1, result1 );
    EXPECT_EQ( 2, sphere_and_plane_collision( A, CC, 0.5, P0, N, result1, result2 ) );
    EXPECT_TRUE( pair_equal( T1, T2, result1, result2 ) );
    EXPECT_EQ( 2, sphere_and_plane_collision( D, A, 0.5, P0, N, result1, result2 ) );
    EXPECT_TRUE( pair_equal( T1, T2, result1, result2 ) );
}
