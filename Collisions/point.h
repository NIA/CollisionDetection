#pragma once
#include <iostream>
#include <cmath>
#include "floating_point.h"

namespace Collisions
{
    class Point
    {
    public:
        double x, y, z;

        Point() : x(0), y(0), z(0) {}
        Point(double x, double y, double z) : x(x), y(y), z(z) {}

        // unary operators
        Point operator-() const
        {
            return Point( -x, -y, -z );
        }
        Point operator+() const
        {
            return *this;
        }

        // assignment operators
        Point & operator+=(const Point &another)
        {
            x += another.x;
            y += another.y;
            z += another.z;
            return *this;
        }
        Point & operator-=(const Point &another)
        {
            x -= another.x;
            y -= another.y;
            z -= another.z;
            return *this;
        }

        Point & operator*=(const double &scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }
        Point & operator/=(const double &scalar)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        // binary operators
        // TODO: double * Point operator
        Point operator+(const Point &another) const
        {
            Point result = *this;
            return result += another;
        }
        Point operator-(const Point &another) const
        {
            Point result = *this;
            return result -= another;
        }

        Point operator*(const double &scalar) const
        {
            Point result = *this;
            return result *= scalar;
        }
        Point operator/(const double &scalar) const
        {
            Point result = *this;
            return result /= scalar;
        }

        bool operator==(const Point &another) const
        {
            return equal(x, another.x) && equal(y, another.y) && equal(z, another.z);
        }
        bool operator!=(const Point &another) const
        {
            return !( *this == another );
        }
        
        // scalar multiplication
        double operator*(const Point &another) const
        {
            return x*another.x + y*another.y + z*another.z;
        }
        
        // methods
        double sqared_norm() const
        {
            return (*this)*(*this);
        }
        double norm() const
        {
            return sqrt( sqared_norm() );
        }
        Point & normalize() // normalizes given point/vector in place (!), returns itself
        {
            if( norm() != 0 )
            {
                (*this) /= norm();
            }
            return *this;
        }
        Point normalized() const  // returns normalized point/vector
        {
            Point result = *this;
            return result.normalize();
        }            
    };

    typedef Point Vector;

    // more operators
    inline std::ostream &operator<<(std::ostream &stream, Point const &point)
    {
        return stream << "(" << point.x << ", " << point.y << ", " << point.z << ")";
    }
};