#include "../Collisions/vector.h"
#include <gtest/gtest.h>

using namespace Collisions;
// TODO: make test variables constants

TEST(PointTest, DefaultConstruct)
{
    Point p;
    EXPECT_EQ( 0, p.x );
    EXPECT_EQ( 0, p.y );
    EXPECT_EQ( 0, p.z );
}

TEST(PointTest, Construct)
{
    Point p( 2, 3, 4.8 );
    EXPECT_EQ( 2.0, p.x );
    EXPECT_EQ( 3.0, p.y );
    EXPECT_EQ( 4.8, p.z );
}

TEST(PointTest, CopyConstruct)
{
    Point p( 2, 3, 4.8 );
    Point p1( p );
    Point p2 = p;
    EXPECT_EQ( p, p1 );
    EXPECT_EQ( p, p2 );
}

TEST(PointTest, Equal)
{
    Point p1a( 2, 3, 4.8 );
    Point p1b( 2, 3, 4.8 );
    Point p2( 1, 5, 3.1 );
    EXPECT_TRUE( p1a == p1a );
    EXPECT_TRUE( p1a == p1b );
    EXPECT_FALSE( p1a == p2 );
}

TEST(PointTest, NotEqual)
{
    Point p1a( 2, 3, 4.8 );
    Point p1b = p1a;
    Point p2( 1, 5, 3.1 );
    EXPECT_FALSE( p1a != p1a );
    EXPECT_FALSE( p1a != p1b );
    EXPECT_TRUE( p1a != p2 );
}

TEST(PointTest, UnaryPlus)
{
    Point p( 2, 3, 4.8 );
    EXPECT_EQ( p, +p );
}

TEST(PointTest, UnaryMinus)
{
    Point p( 2, 3, 4.8 );
    Point p1( -2, -3, -4.8 );
    EXPECT_EQ( p1, -p );
}

TEST(PointTest, AddAssign)
{
    Point p1( 2, 3, 4.8 );
    Point p2( 1, -8, 1.1 );
    Point p3( p1.x + p2.x, p1.y + p2.y, p1.z + p2.z );
    EXPECT_EQ( &p1, &(p1 += p2) ); // It actually returns first argument

    EXPECT_EQ( p3, p1 );
}

TEST(PointTest, SubAssign)
{
    Point p1( 2, 3, 4.8 );
    Point p2( 1, -8, 1.1 );
    Point p3( p1.x - p2.x, p1.y - p2.y, p1.z - p2.z );
    EXPECT_EQ( &p1, &(p1 -= p2) ); // It actually returns first argument

    EXPECT_EQ( p3, p1 );
}

TEST(PointTest, Add)
{
    Point p1( 2, 3, 4.8 );
    Point p2( 1, -8, 1.1 );
    Point p3( p1.x + p2.x, p1.y + p2.y, p1.z + p2.z );

    EXPECT_EQ( p3, p1 + p2 );
}

TEST(PointTest, Subtract)
{
    Point p1( 2, 3, 4.8 );
    Point p2( 1, -8, 1.1 );
    Point p3( p1.x - p2.x, p1.y - p2.y, p1.z - p2.z );

    EXPECT_EQ( p3, p1 - p2 );
}

TEST(PointTest, MulAssign)
{
    Point p1( 2, 3, 4.8 );
    double d = 2.3;
    Point p3( p1.x*d, p1.y*d, p1.z*d );
    EXPECT_EQ( &p1, &(p1 *= d) ); // It actually returns first argument

    EXPECT_EQ( p3, p1 );
}

TEST(PointTest, DivAssign)
{
    Point p1( 2, 3, 4.8 );
    double d = 2.3;
    Point p3( p1.x/d, p1.y/d, p1.z/d );
    EXPECT_EQ( &p1, &(p1 /= d) ); // It actually returns first argument

    EXPECT_EQ( p3, p1 );
}

TEST(PointTest, Multiply)
{
    Point p1( 2, 3, 4.8 );
    double d = 2.3;
    Point p3( p1.x*d, p1.y*d, p1.z*d );

    EXPECT_EQ( p3, p1*d );
    EXPECT_EQ( p3, d*p1 );
}

TEST(PointTest, Divide)
{
    Point p1( 2, 3, 4.8 );
    double d = 2.3;
    Point p3( p1.x/d, p1.y/d, p1.z/d );

    EXPECT_EQ( p3, p1/d );
}

TEST(PointTest, ScalarMultiply)
{
    double a = 2, b = 3, c = 4.8;
    double d = 1, e = 0, f = -4.1;
    Point p1(a, b, c);
    Point p2(d, e, f);

    EXPECT_DOUBLE_EQ( a*d + b*e + c*f, p1*p2 );
}

TEST(PointTest, SqaredNorm)
{
    Point p1(1, 2, 3);
    Point p2(1, -1, 0);

    EXPECT_DOUBLE_EQ( 14, p1.sqared_norm() );
    EXPECT_DOUBLE_EQ(  2, p2.sqared_norm() );
}

TEST(PointTest, Norm)
{
    Point p(3, -4, 0);
    EXPECT_DOUBLE_EQ( 5, p.norm() );
}

TEST(PointTest, Normalize)
{
    Point p(3, -4, 0);
    Point p1(3.0/5, -4.0/5, 0);
    EXPECT_EQ( &p, &( p.normalize() ) ); // It actually returns point itself
    EXPECT_EQ( p1, p );
    
    // Test normalizing when norm is 0
    Point zero1(0, 0, 0);
    Point zero2(0, 0, 0);
    zero1.normalize();
    EXPECT_EQ( zero2, zero1 );
}

TEST(PointTest, Normalized)
{
    Point p(3, -4, 0);
    Point p1(3.0/5, -4.0/5, 0);
    EXPECT_EQ( p1, p.normalized() );
}

TEST(PointTest, Distance)
{
    Point p1(1, 2, -3);
    Point p2(4, -2, -3);
    EXPECT_DOUBLE_EQ( 5, distance(p1, p2) );
}

TEST(PointTest, VectorMultiply)
{
    Vector ex(1, 0, 0);
    Vector ey(0, 1, 0);
    Vector ez(0, 0, 1);
    Vector ZERO(0, 0, 0);
    
    Vector v1(1, 0, -1);
    Vector v2(0, 1, -1);
    Vector v3(1, 1, 1);
    v3.normalize();
    v3 *= v1.norm()*v2.norm()*sin( acos( v1.normalized()*v2.normalized()) ); // area of parallelogram

    EXPECT_EQ( ez, cross_product(ex, ey) );
    EXPECT_EQ( -ez, cross_product(ey, ex) );
    EXPECT_EQ( ZERO, cross_product(ex, ex) );

    EXPECT_EQ( v3, cross_product(v1, v2) );
}

TEST(PointTest, IsZero)
{
    Point ZERO(0, 0, 0);
    Point NON_ZERO(0, 0.001, 0);

    EXPECT_TRUE( ZERO.is_zero() );
    EXPECT_FALSE( NON_ZERO.is_zero() );
}

TEST(PointTest, IsCollinearTo)
{
    Vector v1(1, 0, -1);
    Vector v2(0, 1, -1);

    EXPECT_FALSE( v1.is_collinear_to(v2) );
    EXPECT_FALSE( v2.is_collinear_to(v1) );
    EXPECT_TRUE( v1.is_collinear_to(v1) );
    EXPECT_TRUE( v1.is_collinear_to(-35.8*v1) );
}

TEST(PointTest, IsOrthogonalTo)
{
    Vector v1 (1, 0, 1);
    Vector v11(1, 1, 1);
    Vector v2 (0, 1, 0);

    EXPECT_FALSE( v1.is_orthogonal_to(v1) );
    EXPECT_FALSE( v1.is_orthogonal_to(-35.8*v1) );
    EXPECT_FALSE( v1.is_orthogonal_to(v11) );
    EXPECT_TRUE( v1.is_orthogonal_to(v2) );
    EXPECT_TRUE( v2.is_orthogonal_to(v1) );
}

// Triangle class tests

TEST(TriangleTest, Creation)
{
    Point A(1,2,3), B(2,3,4), C(3,3,3);
    Triangle triangle(A, B, C);

    EXPECT_EQ(A, triangle[0]);
    EXPECT_EQ(B, triangle[1]);
    EXPECT_EQ(C, triangle[2]);
}

TEST(TriangleTest, Normal)
{
    Point A(1,0,0), B(0,0,1), C(0,1,0);
    Triangle triangle(A, B, C);

    Vector expected_normal = Vector(1, 1, 1).normalized();
    
    EXPECT_EQ( expected_normal, triangle.normal() );
}

TEST(TriangleTest, SideNormal)
{
    Triangle triangle( Point(0,0,0), Point(1,2,0), Point(3,0,0) );

    EXPECT_EQ( Vector(-2,1,0).normalized(), triangle.side_outer_normal(0) );
    EXPECT_EQ( Vector(1, 1,0).normalized(), triangle.side_outer_normal(1) );
    EXPECT_EQ( Vector(0,-1,0).normalized(), triangle.side_outer_normal(2) );
}

TEST(TriangleTest, BlackTest)
{
    Point A(1,2,3), B(2,3,4), C(3,4,5);
    Triangle triangle(A, B, C);
    
    EXPECT_THROW( triangle[3], OutOfBoundsError );
    EXPECT_THROW( triangle.side_outer_normal(3), OutOfBoundsError );
    EXPECT_THROW( triangle.normal(), DegeneratedTriangleError );
}

