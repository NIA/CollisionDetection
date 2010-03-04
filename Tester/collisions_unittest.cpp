#include "../Collisions/collisions.h"
#include <gtest/gtest.h>

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

TEST(LineAndPlaneTest, BlackTest)
{
    Point A(1, 1, 1);
    Vector L(0, 0, -2);

    Vector ZERO(0, 0, 0);
    Point result;

    EXPECT_THROW( line_and_plane_collision( A, ZERO, A, L, result ), InvalidLineVectorError );
    EXPECT_THROW( line_and_plane_collision( A, L, A, ZERO, result ), InvalidNormalError );
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

TEST(SegmentAndPlaneTest, BlackTest)
{
    Point A(1, 1, 1);
    Point B(1, 1, 2);
    Vector N(0, 0, 1);
    Vector ZERO(0, 0, 0);
    
    Point result;

    EXPECT_THROW( segment_and_plane_collision( A, A, A, N, result ), DegeneratedSegmentError );
    EXPECT_THROW( segment_and_plane_collision( A, B, A, ZERO, result ), InvalidNormalError );
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

TEST(SphereAndPlaneTest, BlackTest)
{
    Point A(1, 1, 1);
    Point B(3, 1, 1);

    Vector N(0, 0, 1);

    Vector ZERO( 0, 0, 0 );
    
    Point result;

    EXPECT_THROW( sphere_and_plane_collision( A, B, 0.5, A, ZERO, result ), InvalidNormalError );
    EXPECT_THROW( sphere_and_plane_collision( A, A, 0.5, A, N, result ), DegeneratedSegmentError );
}

// Sphere and point tests

TEST(SphereAndPointTest, Trivial)
{
    Point P(2.5, 0, 0);

    Point A(0, 0, 1.1);
    Point C(0, 0, 0.1);
    Point H(0, 0, 0); // nearest point
    Point B(0, 0, -1.2);

    EXPECT_TRUE(  sphere_and_point_collision( A, B, 2.6, P ) );
    EXPECT_FALSE( sphere_and_point_collision( A, B, 2.4, P ) );
    EXPECT_TRUE(  sphere_and_point_collision( A, H, 2.6, P ) );
    EXPECT_FALSE( sphere_and_point_collision( A, H, 2.4, P ) );
    EXPECT_TRUE(  sphere_and_point_collision( H, B, 2.6, P ) );
    EXPECT_FALSE( sphere_and_point_collision( H, B, 2.4, P ) );
    EXPECT_TRUE(  sphere_and_point_collision( B, C, 2.6, P ) );
    EXPECT_FALSE( sphere_and_point_collision( B, C, 2.4, P ) );
    EXPECT_TRUE(  sphere_and_point_collision( A, C, distance( P, C ), P ) );
    EXPECT_FALSE( sphere_and_point_collision( A, C, distance( P, C )/2, P ) );
}

TEST(SphereAndPointTest, Arbitrary)
{
    Point P(0, 0, 0);

    Point A(0, 0, 1);
    Point H(1.0/3, 1.0/3, 1.0/3); // nearest point
    Point C(0.5, 0.5, 0);
    Point B(1, 1, -1);

    double dst = 1.0/sqrt(3.0);
    double dst_more = dst*2;
    double dst_less = dst/2;

    EXPECT_TRUE(  sphere_and_point_collision( A, B, dst_more, P ) );
    EXPECT_FALSE( sphere_and_point_collision( A, B, dst_less, P ) );
    EXPECT_TRUE(  sphere_and_point_collision( A, H, dst_more, P ) );
    EXPECT_FALSE( sphere_and_point_collision( A, H, dst_less, P ) );
    EXPECT_TRUE(  sphere_and_point_collision( H, B, dst_more, P ) );
    EXPECT_FALSE( sphere_and_point_collision( H, B, dst_less, P ) );
    EXPECT_TRUE(  sphere_and_point_collision( A, C, dst_more, P ) );
    EXPECT_FALSE( sphere_and_point_collision( A, C, dst_less, P ) );
    EXPECT_TRUE(  sphere_and_point_collision( C, B, distance( P, C )*2, P ) );
    EXPECT_FALSE( sphere_and_point_collision( C, B, distance( P, C )/2, P ) );
}

TEST(SphereAndPointTest, BlackTest)
{
    Point A(1, 1, 1);

    EXPECT_THROW( sphere_and_point_collision( A, A, 0.5, A ), DegeneratedSegmentError );
}

// Sphere and point tests

TEST( SphereAndSegmentTest, Parallel )
{
    Point P1(0,0,0), P2(2,0,0); // segment
    Point A (0,1,0),  B(2,1,0); // sphere segment
    Point temp;

    EXPECT_FALSE( sphere_and_segment_collision( A, B, 0.5, P1, P2, temp ) );
    EXPECT_FALSE( sphere_and_segment_collision( A, B, 1.0, P1, P2, temp ) );
    EXPECT_FALSE( sphere_and_segment_collision( A, B, 1.5, P1, P2, temp ) );
}

TEST(SphereAndSegmentTest, PerpendicularCrossingTrivial)
{
    Point P1(0,0,0), P2(2,0,0); // segment
    Point P(0.2, 0, 0); // P P1 is a part of segment

    double R = 0.25;

    Point A (1,  R+1, 0);  // upper than segment
    Point AA(1,    R, 0);  // sphere is touching the segment, upper
    Point B (1,    0, 0);  // on the segment
    Point CC(1,   -R, 0);  // sphere is touching the segment, lower
    Point C (1, -R-1, 0);  // lower
    Point D (1, -R-5, 0);  // even lower

    Point result;
    
    EXPECT_FALSE( sphere_and_segment_collision(  C,  D, R, P1, P2, result ) );

    EXPECT_TRUE(  sphere_and_segment_collision(  A, AA, R, P1, P2, result ) );
    EXPECT_EQ( B, result );
    EXPECT_FALSE( sphere_and_segment_collision( AA,  A, R, P1, P2, result ) );

    EXPECT_TRUE(  sphere_and_segment_collision(  A, CC, R, P1, P2, result ) );
    EXPECT_EQ( B, result );
    EXPECT_TRUE(  sphere_and_segment_collision( CC,  A, R, P1, P2, result ) );
    EXPECT_EQ( B, result );

    EXPECT_TRUE(  sphere_and_segment_collision(  A,  C, R, P1, P2, result ) );
    EXPECT_EQ( B, result );
    EXPECT_TRUE(  sphere_and_segment_collision(  C,  A, R, P1, P2, result ) );
    EXPECT_EQ( B, result );

    EXPECT_FALSE(  sphere_and_segment_collision(  A,  C, R, P1, P, result ) );
    EXPECT_FALSE(  sphere_and_segment_collision(  C,  A, R, P1, P, result ) );
}

TEST(SphereAndSegmentTest, PerpendicularTrivial)
{
    Point P1(0,0,0), P2(2,0,0); // segment
    double R = 0.5;
    double height = 0.3;
    double d = sqrt( R*R - height*height );

    Point A (1,  d+1, height);  // upper than segment
    Point AU(1, d+0.001, height);  // sphere almost touching the segment, but a little upper
    Point AA(1,    d, height);  // sphere is touching the segment, upper
    Point B (1,    0, height);  // over the segment
    Point CC(1,   -d, height);  // sphere is touching the segment, lower
    Point C (1, -d-1, height);  // lower
    Point D (1, -d-5, height);  // even lower
    
    Point H (1,    0,      0);  // touch point

    Point result;
    
    EXPECT_FALSE( sphere_and_segment_collision(  C,  D, R, P1, P2, result ) );

    EXPECT_TRUE(  sphere_and_segment_collision(  A, AA, R, P1, P2, result ) );
    EXPECT_EQ( H, result );
    EXPECT_FALSE( sphere_and_segment_collision(  A, AU, R, P1, P2, result ) );
    EXPECT_FALSE( sphere_and_segment_collision( AA,  A, R, P1, P2, result ) );

    EXPECT_TRUE(  sphere_and_segment_collision(  A, CC, R, P1, P2, result ) );
    EXPECT_EQ( H, result );
    EXPECT_TRUE(  sphere_and_segment_collision( CC,  A, R, P1, P2, result ) );
    EXPECT_EQ( H, result );

    EXPECT_TRUE(  sphere_and_segment_collision(  A,  C, R, P1, P2, result ) );
    EXPECT_EQ( H, result );
    EXPECT_TRUE(  sphere_and_segment_collision(  C,  A, R, P1, P2, result ) );
    EXPECT_EQ( H, result );
}

TEST(SphereAndSegmentTest, Arbitrary)
{
    Point P1(0,0,0), P2(2,0,0); // segment
    double R = 0.5;
    double height = 0.3;
    double d = sqrt( R*R - height*height );

    // sphere flies by the line y=1-x; z=height
    Point A ( 1-(d+1),  d+1, height);
    double AUy = d + 0.001;
    Point AU( 1 - AUy,  AUy, height);
    Point AA(   1 - d,    d, height);
    Point B (       1,    0, height);
    Point CC(   1 + d,   -d, height);
    Point C ( 1+(d+1), -d-1, height);
    Point D ( 1+(d+5), -d-5, height);
    
    Point H1(   1 - d,    0,      0);  // touch point
    Point H2(   1 + d,    0,      0);  // touch point

    Point result;
    
    EXPECT_FALSE( sphere_and_segment_collision(  C,  D, R, P1, P2, result ) );

    EXPECT_TRUE(  sphere_and_segment_collision(  A, AA, R, P1, P2, result ) );
    EXPECT_EQ( H1, result );
    EXPECT_FALSE( sphere_and_segment_collision(  A, AU, R, P1, P2, result ) );
    EXPECT_FALSE( sphere_and_segment_collision( AA,  A, R, P1, P2, result ) );

    EXPECT_TRUE(  sphere_and_segment_collision(  A,  B, R, P1, P2, result ) );
    EXPECT_EQ( H1, result );
    EXPECT_FALSE( sphere_and_segment_collision(  B,  A, R, P1, P2, result ) );

    EXPECT_TRUE(  sphere_and_segment_collision(  A, CC, R, P1, P2, result ) );
    EXPECT_EQ( H1, result );
    EXPECT_TRUE(  sphere_and_segment_collision( CC,  A, R, P1, P2, result ) );
    EXPECT_EQ( H2, result );

    EXPECT_TRUE(  sphere_and_segment_collision(  A,  C, R, P1, P2, result ) );
    EXPECT_EQ( H1, result );
    EXPECT_TRUE(  sphere_and_segment_collision(  C,  A, R, P1, P2, result ) );
    EXPECT_EQ( H2, result );
}

TEST(SphereAndSegmentTest, BlackTest)
{
    Point A(1, 1, 1);
    Point B(3, 1, 1);
    Point temp;

    EXPECT_THROW( sphere_and_segment_collision( A, A, 0.5, A, B, temp ), DegeneratedSegmentError );
    EXPECT_THROW( sphere_and_segment_collision( A, B, 0.5, A, A, temp ), DegeneratedSegmentError );
}

TEST(SphereAndTriangleTest, TouchingPlane)
{
    double R = 0.32;
    Triangle triangle( Point(0,0,0), Point(2,4,0), Point(5,0,0) );
    Point inner(2,2,0);
    Point outer( 3, -1.5*R, 0);
    Vector L( 0, 0, 2*R );
    
    Point upper1 = inner + L;
    Point upper2 = outer + L;

    Point result;
    
    EXPECT_TRUE(  sphere_and_triangle_collision( inner-L, inner+L, R, triangle, result ) );
    EXPECT_EQ( inner, result );
    EXPECT_FALSE( sphere_and_triangle_collision( outer-L, outer+L, R, triangle, result ) );
    EXPECT_FALSE( sphere_and_triangle_collision(  upper1,  upper2, R, triangle, result ) );
}

TEST(SphereAndTriangleTest, TouchingNearestSide)
{
    double R = 0.32;
    Triangle triangle( Point(0,0,0), Point(2,4,0), Point(5,0,0) );
    Point on_side(4,0,0);
    Vector L( 0, 1, 0 );
    Point A = on_side + (6 + R)*L;
    Point B = on_side - 2*R*L;

    Point result;
    
    EXPECT_TRUE(  sphere_and_triangle_collision( B, A, R, triangle, result ) );
    EXPECT_EQ( on_side, result );
    // now lets launch it backwards
    EXPECT_TRUE(  sphere_and_triangle_collision( A, B, R, triangle, result ) );
    EXPECT_NE( on_side, result ); // TODO: calculate actual touch point for another side
}

TEST(SphereAndTriangleTest, TouchingVertexNotSide)
{
    double R = 0.32;
    Triangle triangle( Point(0,0,0), Point(2,4,0), Point(5,0,0) );
    Point A(7,-1,0);
    Point B(3,+1,0);

    Point result;
    
    EXPECT_TRUE( sphere_and_triangle_collision( A, B, R, triangle, result ) );
    EXPECT_EQ( triangle[2], result );
}

TEST(SphereAndTriangleTest, TouchingNearestVertex)
{
    double R = 0.32;
    Triangle triangle( Point(0,0,0), Point(2,4,0), Point(5,0,0) );
    Point A = triangle[1] + Point(0,0,R);
    Point B = triangle[0] - Point(R,R,0);

    Point result;
    
    EXPECT_TRUE( sphere_and_triangle_collision( A, B, R, triangle, result ) );
    EXPECT_EQ( triangle[1], result );
    EXPECT_TRUE( sphere_and_triangle_collision( B, A, R, triangle, result ) );
    EXPECT_EQ( triangle[0], result );
}

TEST(SphereAndTriangleTest, OutsideOnly)
{
    double R = 0.32;
    Triangle triangle( Point(0,0,0), Point(2,4,0), Point(5,0,0) );
    Point A(2, 2*R,0);
    Point B(2,-3*R,0);
    
    Point C(2, 4-2*R, 0);
    Point D(2, 4+2*R, 0);

    Point result;
    
    EXPECT_TRUE(  sphere_and_triangle_collision( B, A, R, triangle, result ) );
    EXPECT_FALSE( sphere_and_triangle_collision( A, B, R, triangle, result ) );
    
    EXPECT_TRUE(  sphere_and_triangle_collision( D, C, R, triangle, result ) );
    EXPECT_FALSE( sphere_and_triangle_collision( C, D, R, triangle, result ) );
}

