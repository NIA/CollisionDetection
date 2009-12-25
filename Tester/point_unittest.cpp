#include "../Collisions/point.h"
#include <gtest/gtest.h>

TEST(PointTest, DefaultConstruct)
{
    Point p;
    EXPECT_EQ( p.x, 0 );
    EXPECT_EQ( p.y, 0 );
    EXPECT_EQ( p.z, 0 );
}

TEST(PointTest, Construct)
{
    Point p( 2, 3, 4.8 );
    EXPECT_EQ( p.x, 2.0 );
    EXPECT_EQ( p.y, 3.0 );
    EXPECT_EQ( p.z, 4.8 );
}

TEST(PointTest, CopyConstruct)
{
    Point p( 2, 3, 4.8 );
    Point p1( p );
    Point p2 = p;
    EXPECT_TRUE( p == p1 );
    EXPECT_TRUE( p == p2 );
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
    EXPECT_TRUE( +p == p ); // TODO: To use EXPECT_EQ the class should define operator << for std::ostream
}

TEST(PointTest, UnaryMinus)
{
    Point p( 2, 3, 4.8 );
    Point p1( -2, -3, -4.8 );
    EXPECT_TRUE( -p == p1 );
}

TEST(PointTest, AddAssign)
{
    Point p1( 2, 3, 4.8 );
    Point p2( 1, -8, 1.1 );
    Point p3( p1.x + p2.x, p1.y + p2.y, p1.z + p2.z );
    EXPECT_EQ( &(p1 += p2), &p1 ); // It actually returns first argument

    EXPECT_TRUE( p1 == p3 );
}

TEST(PointTest, SubAssign)
{
    Point p1( 2, 3, 4.8 );
    Point p2( 1, -8, 1.1 );
    Point p3( p1.x - p2.x, p1.y - p2.y, p1.z - p2.z );
    EXPECT_EQ( &(p1 -= p2), &p1 ); // It actually returns first argument

    EXPECT_TRUE( p1 == p3 );
}

TEST(PointTest, Add)
{
    Point p1( 2, 3, 4.8 );
    Point p2( 1, -8, 1.1 );
    Point p3( p1.x + p2.x, p1.y + p2.y, p1.z + p2.z );

    EXPECT_TRUE( p1 + p2 == p3 );
}

TEST(PointTest, Subtract)
{
    Point p1( 2, 3, 4.8 );
    Point p2( 1, -8, 1.1 );
    Point p3( p1.x - p2.x, p1.y - p2.y, p1.z - p2.z );

    EXPECT_TRUE( p1 - p2 == p3 );
}

TEST(PointTest, MulAssign)
{
    Point p1( 2, 3, 4.8 );
    double d = 2.3;
    Point p3( p1.x*d, p1.y*d, p1.z*d );
    EXPECT_EQ( &(p1 *= d), &p1 ); // It actually returns first argument

    EXPECT_TRUE( p1 == p3 );
}

TEST(PointTest, DivAssign)
{
    Point p1( 2, 3, 4.8 );
    double d = 2.3;
    Point p3( p1.x/d, p1.y/d, p1.z/d );
    EXPECT_EQ( &(p1 /= d), &p1 ); // It actually returns first argument

    EXPECT_TRUE( p1 == p3 );
}

TEST(PointTest, Multiply)
{
    Point p1( 2, 3, 4.8 );
    double d = 2.3;
    Point p3( p1.x*d, p1.y*d, p1.z*d );

    EXPECT_TRUE( p1*d == p3 );
}

TEST(PointTest, Divide)
{
    // TODO: Expect throw when / 0
    Point p1( 2, 3, 4.8 );
    double d = 2.3;
    Point p3( p1.x/d, p1.y/d, p1.z/d );

    EXPECT_TRUE( p1/d == p3 );
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
