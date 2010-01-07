#pragma once
#include <iostream>
#include <cmath>
#include "errors.h"
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
        // vector multiplication
        Point operator&(const Point &another) const
        {
            return Point( y*another.z - z*another.y, z*another.x - x*another.z, x*another.y - y*another.x );
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
        bool is_zero() const
        {
            return equal(x, 0) && equal(y, 0) && equal(z, 0);
        }
    };

    typedef Point Vector; // define an alias

    // more operators
    inline Point operator*(const double &scalar, const Point &point)
    {
        return point * scalar;
    }
    inline std::ostream &operator<<(std::ostream &stream, const Point &point)
    {
        return stream << "(" << point.x << ", " << point.y << ", " << point.z << ")";
    }

    // functions
    inline double distance(const Point &A, const Point &B)
    {
        return (A - B).norm();
    }

    // error checking functions
    template <class ErrType> inline void check_nonzero_vector( const Vector &vector, const ErrType &error )
    {
        check( !vector.is_zero(), error );
    }
    inline void check_segment( const Point &segment_start, const Point &segment_end )
    {
        check( segment_start != segment_end, DegeneratedSegmentError() );
    }
};
