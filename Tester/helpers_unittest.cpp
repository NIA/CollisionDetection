#include "../Collisions/collisions.h"
#include <gtest/gtest.h>

using namespace Collisions;

// Point between tests

TEST(IsPointBetweenTest, OnSingleLine)
{
    // TODO: define and test behavior if points are not on single line
    const Point p1(0, 0, 0);
    const Point p2(1, 1, 2);
    const Point p3(2, 2, 4);

    EXPECT_TRUE(  is_point_between( p2, p1, p3 ) );
    EXPECT_FALSE( is_point_between( p1, p2, p3 ) );
    EXPECT_FALSE( is_point_between( p3, p2, p1 ) );
    
    EXPECT_TRUE(  is_point_between( p1, p1, p2 ) );
    EXPECT_TRUE(  is_point_between( p2, p1, p2 ) );
}

// Distance between point and line tests
TEST(DistancePointAndLineTest, OnTheLine)
{
    const Point P(0, 0, 0);

    const Point A(0, 0, 1.1);
    const Vector L(0, 0, 2.3); // z axis

    const Point H(0, 0, 0); // nearest point

    Point nearest;

    EXPECT_TRUE( equal( 0.0, distance_between_point_and_line( P, A, L, nearest ) ) );
    EXPECT_EQ( H, nearest );
}


TEST(DistancePointAndLineTest, Trivial)
{
    const Point P(2.5, 0, 0);

    const Point A(0, 0, 1.1);
    const Vector L(0, 0, 11); // z axis

    const Point H(0, 0, 0); // nearest point

    Point nearest;

    EXPECT_DOUBLE_EQ( 2.5, distance_between_point_and_line( P, A, L, nearest ) );
    EXPECT_EQ( H, nearest );
}

TEST(DistancePointAndLineTest, Arbitrary)
{
    const Point P(0, 0, 0);

    const Point A(0, 0, 1);
    const Vector L(0.5, 0.5, -1); // on simplex

    const Point H(1.0/3, 1.0/3, 1.0/3); // nearest point

    Point nearest;

    EXPECT_DOUBLE_EQ( 1.0/sqrt(3.0), distance_between_point_and_line( P, A, L, nearest ) );
    EXPECT_EQ( H, nearest );
}

TEST(DistancePointAndLineTest, BlackTest)
{
    const Point A(0, 0, 1);
    const Vector ZERO(0, 0, 0);

    Point nearest;

    EXPECT_THROW( distance_between_point_and_line( A, A, ZERO, nearest ), InvalidLineVectorError );
}

// Distance between point and line tests

TEST(DistancePointAndSegmentTest, OnTheLine)
{
    const Point P(0, 0, 0);

    const Point A(0, 0, 1.1);
    const Point C(0, 0, 0.1);
    const Point H(0, 0, 0);
    const Point B(0, 0, -1.2);

    EXPECT_TRUE( equal( 0.0, distance_between_point_and_segment( P, A, B ) ) );
    EXPECT_TRUE( equal( 0.0, distance_between_point_and_segment( P, A, H ) ) );
    EXPECT_TRUE( equal( 0.0, distance_between_point_and_segment( P, H, B ) ) );
    EXPECT_TRUE( equal( 0.0, distance_between_point_and_segment( P, B, C ) ) );
    EXPECT_DOUBLE_EQ( 0.1, distance_between_point_and_segment( P, A, C ) );
}

TEST(DistancePointAndSegmentTest, Trivial)
{
    const Point P(2.5, 0, 0);

    const Point A(0, 0, 1.1);
    const Point C(0, 0, 0.1);
    const Point H(0, 0, 0); // nearest point
    const Point B(0, 0, -1.2);

    EXPECT_DOUBLE_EQ( 2.5, distance_between_point_and_segment( P, A, B ) );
    EXPECT_DOUBLE_EQ( 2.5, distance_between_point_and_segment( P, A, H ) );
    EXPECT_DOUBLE_EQ( 2.5, distance_between_point_and_segment( P, H, B ) );
    EXPECT_DOUBLE_EQ( 2.5, distance_between_point_and_segment( P, B, C ) );
    EXPECT_DOUBLE_EQ( distance( P, C ), distance_between_point_and_segment( P, A, C ) );
}

TEST(DistancePointAndSegmentTest, Arbitrary)
{
    const Point P(0, 0, 0);

    const Point A(0, 0, 1);
    const Point H(1.0/3, 1.0/3, 1.0/3); // nearest point
    const Point C(0.5, 0.5, 0);
    const Point B(1, 1, -1);

    const double dst = 1.0/sqrt(3.0);

    EXPECT_DOUBLE_EQ( dst, distance_between_point_and_segment( P, A, B ) );
    EXPECT_DOUBLE_EQ( dst, distance_between_point_and_segment( P, A, H ) );
    EXPECT_DOUBLE_EQ( dst, distance_between_point_and_segment( P, H, B ) );
    EXPECT_DOUBLE_EQ( dst, distance_between_point_and_segment( P, A, C ) );
    EXPECT_DOUBLE_EQ( distance( P, C ), distance_between_point_and_segment( P, C, B ) );
}

TEST(DistancePointAndSegmentTest, BlackTest)
{
    const Point A(0, 0, 1);

    EXPECT_THROW( distance_between_point_and_segment( A, A, A ), DegeneratedSegmentError );
}

// Distance between two lines tests

TEST(DistanceTwoLinesTest, Crossing)
{
    const Point A1(0.2, 0.2, 0.2);
    const Vector L1(0.99, 0.99, 0.99); // simplex normal

    const Point A2(0, 0, 1);
    const Vector L2(0.5, 0.5, -1); // on simplex

    EXPECT_TRUE( equal( 0.0, distance_between_two_lines( A1, L1, A2, L2 ) ) );
}

TEST(DistanceTwoLinesTest, PerpendicularTrivial)
{
    const Point A1(0.2, 0, 0);
    const Vector L1(0.99, 0, 0); // x axis

    const Point A2(0, 2.3, 2.3);
    const Vector L2(0, -5, 0); // y axis (shifted 2.3 up)

    EXPECT_DOUBLE_EQ( 2.3, distance_between_two_lines( A1, L1, A2, L2 ) );
}

TEST(DistanceTwoLinesTest, NonParallelArbitrary)
{
    const Point A1(0.5, 0.5, 0);
    const Vector L1(-0.5, 0, 0.5); // on little simplex (1x1x1)

    const Point A2(5.0/3, 1.0/3, 0);
    const Vector L2(1.0/6, 1.0/6, -1.0/3); // on big simplex (2x2x2)

    EXPECT_DOUBLE_EQ( 1.0/sqrt(3.0),  distance_between_two_lines( A1, L1, A2, L2 ) );
}

TEST(DistanceTwoLinesTest, ParallelTrivial)
{
    const Point A1(0.2, 0, 0);
    const Vector L1(0.99, 0, 0); // x axis

    const Point A2(2.3, 0, 2.3);
    const Vector L2(-5, 0, 0); // x axis (shifted 2.3 up)

    EXPECT_DOUBLE_EQ( 2.3, distance_between_two_lines( A1, L1, A2, L2 ) );
}

TEST(DistanceTwoLinesTest, ParallelArbitrary)
{
    const Point A1(0.2, 0, 0);
    const Vector L1(1, 1, 1);

    const Vector N(1, 1, -2); // perpendicular to L1

    const Vector L2 = L1;
    const Point A2 = A1 + 5*N.normalized() + 8*L2;

    EXPECT_DOUBLE_EQ( 5, distance_between_two_lines( A1, L1, A2, L2 ) );
}

TEST(DistanceTwoLinesTest, BlackTest)
{
    const Point A1(0, 0, 0);
    const Vector L1(1, 1, 1);

    const Point A2(0, 0, 1);
    const Vector L2(0.5, 0.5, -1);

    const Vector ZERO(0, 0, 0);

    EXPECT_THROW( distance_between_two_lines( A1, ZERO, A2, L2 ), InvalidLineVectorError );
    EXPECT_THROW( distance_between_two_lines( A1, L1, A2, ZERO ), InvalidLineVectorError );
    EXPECT_THROW( distance_between_two_lines( ZERO, ZERO, ZERO, ZERO ), InvalidLineVectorError );
}

// Nearest points on lines tests

TEST(NearestPointsOnLinesTest, Crossing)
{
    const Point A1(0.2, 0.2, 0.2);
    const Vector L1(0.99, 0.99, 0.99); // simplex normal

    const Point A2(0, 0, 1);
    const Vector L2(0.5, 0.5, -1); // on simplex

    Point result1, result2, temp;
    nearest_points_on_lines(A1, L1, A2, L2, result1, result2);

    // check if result1 and result2 both equal to crossing point
    EXPECT_EQ( result1, result2 );                                                          // check if they are equal
    EXPECT_TRUE( equal( 0.0, distance_between_point_and_line( result1, A1, L1, temp ) ) );  // check if they are on first line
    EXPECT_TRUE( equal( 0.0, distance_between_point_and_line( result1, A2, L2, temp ) ) );  // check if they are on second line
}

TEST(NearestPointsOnLinesTest, PerpendicularTrivial)
{
    const Point A1(0.2, 0, 0);
    const Vector L1(0.99, 0, 0); // x axis

    const Point A2(0, 2.3, 2.3);
    const Vector L2(0, -5, 0); // y axis (shifted 2.3 up)

    Point result1, result2;
    nearest_points_on_lines( A1, L1, A2, L2, result1, result2 );

    EXPECT_EQ( Point(0, 0, 0), result1 );
    EXPECT_EQ( Point(0, 0, 2.3), result2 );
}

TEST(NearestPointsOnLinesTest, NonParallelArbitrary)
{
    const Point A1(1.0/3, 1.0/3, 1.0/3);
    const Vector L1(-0.5, 0, 0.5); // on little simplex (1x1x1)

    const Point A2(2.0/3, 2.0/3, 2.0/3);
    const Vector L2(1.0/6, 1.0/6, -1.0/3); // on big simplex (2x2x2)

    Point result1, result2;
    nearest_points_on_lines( A1, L1, A2, L2, result1, result2 );

    EXPECT_EQ( A1, result1 );
    EXPECT_EQ( A2, result2 );
}

TEST(NearestPointsOnLinesTest, ParallelTrivial)
{
    const Point A1(0.2, 0, 0);
    const Vector L1(0.99, 0, 0); // x axis

    const Point A2(2.3, 0, 2.3);
    const Vector L2(-5, 0, 0); // x axis (shifted 2.3 up)

    Point result1, result2, temp;
    nearest_points_on_lines( A1, L1, A2, L2, result1, result2 );

    EXPECT_DOUBLE_EQ( 2.3, distance( result1, result2 ) );                                  // check if they are really nearest
    EXPECT_TRUE( equal( 0.0, distance_between_point_and_line( result1, A1, L1, temp ) ) );  // check if first is on first line
    EXPECT_TRUE( equal( 0.0, distance_between_point_and_line( result2, A2, L2, temp ) ) );  // check if second is on second line
}

TEST(NearestPointsOnLinesTest, ParallelArbitrary)
{
    const Point A1(0.2, 0, 0);
    const Vector L1(1, 1, 1);

    const Vector N(1, 1, -2); // perpendicular to L1

    const Vector L2 = L1;
    const Point A2N = A1 + 5*N.normalized();
    const Point A2 = A2N + 8*L2;

    Point result1, result2, temp;
    nearest_points_on_lines( A1, L1, A2, L2, result1, result2 );

    EXPECT_DOUBLE_EQ( 5.0, distance( result1, result2 ) );                                  // check if they are really nearest
    EXPECT_TRUE( equal( 0.0, distance_between_point_and_line( result1, A1, L1, temp ) ) );  // check if first is on first line
    EXPECT_TRUE( equal( 0.0, distance_between_point_and_line( result2, A2, L2, temp ) ) );  // check if second is on second line
}

TEST(NearestPointsOnLinesTest, BlackTest)
{
    const Point A1(0, 0, 0);
    const Vector L1(1, 1, 1);

    const Point A2(0, 0, 1);
    const Vector L2(0.5, 0.5, -1);

    const Vector ZERO(0, 0, 0);

    Point temp1, temp2;

    EXPECT_THROW( nearest_points_on_lines( A1, ZERO, A2, L2, temp1, temp2 ), InvalidLineVectorError );
    EXPECT_THROW( nearest_points_on_lines( A1, L1, A2, ZERO, temp1, temp2 ), InvalidLineVectorError );
    EXPECT_THROW( nearest_points_on_lines( ZERO, ZERO, ZERO, ZERO, temp1, temp2 ), InvalidLineVectorError );
}

// Point inside triangle tests

TEST(PointInsideTriangleTest, OutsideFlat)
{
    const Triangle triangle( Point(0,0,0), Point(3,0,0), Point(2,3,0) );
    const Point outsiders[] = { 
                                Point(0,3,0),
                                Point(3,3,0),
                                Point(1, 1.6, 0),
                                Point(1, -0.001, 0),
                                Point(100, -100, 0)
                              };
    for( unsigned i = 0; i < sizeof(outsiders)/sizeof(outsiders[0]); ++i)
    {
        EXPECT_FALSE( is_point_inside_triangle( outsiders[i], triangle ) ) 
            << "Point " << outsiders[i] << " is not inside";
    }
}

TEST(PointInsideTriangleTest, InsideFlat)
{
    const Triangle triangle( Point(0,0,0), Point(3,0,0), Point(2,3,0) );
    const Point insiders[] = { 
                                Point(2,1,0),
                                Point(1,1,0),
                                Point(2,2,0),
                                Point(0.2, 0.2*1.4999, 0),
                              };
    for( unsigned i = 0; i < sizeof(insiders)/sizeof(insiders[0]); ++i)
    {
        EXPECT_TRUE( is_point_inside_triangle( insiders[i], triangle ) ) 
            << "Point " << insiders[i] << " is not outside";
    }
}

TEST(PointInsideTriangleTest, BorderFlat)
{
    const Triangle triangle( Point(0,0,0), Point(3,0,0), Point(2,3,0) );
    const Point on_border[] = { 
                                triangle[0],
                                triangle[1],
                                triangle[2],
                                Point(1,   1.5, 0),
                                Point(1.5, 0,   0),
                                Point(2.5, 1.5, 0),
                              };
    for( unsigned i = 0; i < sizeof(on_border)/sizeof(on_border[0]); ++i)
    {
        EXPECT_TRUE( is_point_inside_triangle( on_border[i], triangle ) ) 
            << "Point " << on_border[i] << " is on border, not outside";
    }
}

TEST(PointInsideTriangleTest, OutsideSimplex)
{
    const Triangle triangle( Point(1,0,0), Point(0,1,0), Point(0,0,1) );
    const Point outsiders[] = { 
                                Point(1.5,0.5,0),
                                Point(0.1,-0.1,1),
                                Point(0.6, -0.1, 0.5),
                                Point(0.5+0.001/2, 0.5+0.001, -0.001),
                                Point(100, -50, -49)
                              };
    for( unsigned i = 0; i < sizeof(outsiders)/sizeof(outsiders[0]); ++i)
    {
        EXPECT_FALSE( is_point_inside_triangle( outsiders[i], triangle ) ) 
            << "Point " << outsiders[i] << " is not inside";
    }
}

TEST(PointInsideTriangleTest, InsideSimplex)
{
    const Triangle triangle( Point(1,0,0), Point(0,1,0), Point(0,0,1) );
    const Point insiders[] = { 
                                Point(1.0/3, 1.0/3, 1.0/3),
                                Point(0.5-0.001/2, 0.5-0.001, +0.001),
                              };
    for( unsigned i = 0; i < sizeof(insiders)/sizeof(insiders[0]); ++i)
    {
        EXPECT_TRUE( is_point_inside_triangle( insiders[i], triangle ) ) 
            << "Point " << insiders[i] << " is not outside";
    }
}

TEST(PointInsideTriangleTest, BorderSimplex)
{
    const Triangle triangle( Point(1,0,0), Point(0,1,0), Point(0,0,1) );
    const Point on_border[] = { 
                                triangle[0],
                                triangle[1],
                                triangle[2],
                                Point(0.5, 0, 0.5),
                                Point(0.75, 0.25,   0),
                                Point(0.1, 0, 0.9),
                              };
    for( unsigned i = 0; i < sizeof(on_border)/sizeof(on_border[0]); ++i)
    {
        EXPECT_TRUE( is_point_inside_triangle( on_border[i], triangle ) ) 
            << "Point " << on_border[i] << " is on border, not outside";
    }
}

TEST(PointInsideTriangleTest, BlackTest)
{
    const Point A(0,0,0);
    const Point B(3,0,0);
    const Point C(2,3,0);
    const Point AB(2,0,0);

    EXPECT_THROW( is_point_inside_triangle( C, Triangle(A, AB, B) ), DegeneratedTriangleError );
    EXPECT_THROW( is_point_inside_triangle( C, Triangle(A, A, B) ), DegeneratedTriangleError );
    EXPECT_THROW( is_point_inside_triangle( C, Triangle(A, A, A) ), DegeneratedTriangleError );
}

// Perpendicular base tests

TEST(PerpendicularBaseTest, Sloping)
{
    const double sloping_coef = 3.4; // L2 is horisontal, while L1 is sloped N:1, where N is sloping_coef
    const Point A(1, 1, 1);
    const Vector L1(-1, -sloping_coef, 0);
    const Vector L2( 1,  0, 0);
    const double length = 2.3;

    const Point first = A + length/sloping_coef*L2;
    const Point second = A - length/sloping_coef*L2;

    EXPECT_EQ( first, perpendicular_base( L1, L2, A, length ) );
    EXPECT_EQ( first, perpendicular_base( L1, -L2, A, length ) );
    EXPECT_EQ( second, perpendicular_base( -L1, L2, A, length ) );
    EXPECT_EQ( second, perpendicular_base( -L1, -L2, A, length ) );
}

TEST(PerpendicularBaseTest, Perpendicular)
{
    const Point A(1, 1, 1);
    const Vector L1( 0, -1, 0);
    const Vector L2( 1,  0, 0);
    const double length = 2.3;

    EXPECT_EQ( A, perpendicular_base( L1, L2, A, length ) );
}

TEST(PerpendicularBaseTest, Parallel)
{
    const Point A(1, 1, 1);
    const Vector L1( 0, -1, 0);
    const double length = 2.3;

    EXPECT_THROW( perpendicular_base( L1, L1, A, length ), ParallelLinesError );
    EXPECT_THROW( perpendicular_base( L1, -4*L1, A, length ), ParallelLinesError );
}

TEST(PerpendicularBaseTest, BlackTest)
{
    const Point A(0, 0, 0);
    const Vector L1(1, 1, 1);
    const Vector L2(0.5, 0.5, -1);

    const Vector ZERO(0, 0, 0);

    EXPECT_THROW( perpendicular_base( L1, ZERO, A, 1.5 ), InvalidLineVectorError );
    EXPECT_THROW( perpendicular_base( ZERO, L2, A, 1.5 ), InvalidLineVectorError );
    EXPECT_THROW( perpendicular_base( ZERO, ZERO, ZERO, 0.0 ), InvalidLineVectorError );
}
