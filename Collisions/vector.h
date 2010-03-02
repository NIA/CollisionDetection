#pragma once
#include <iostream>
#include <cmath>
#include "errors.h"
#include "floating_point.h"

namespace Collisions
{
    class Vector
    {
    public:
        double x, y, z;

        Vector() : x(0), y(0), z(0) {}
        Vector(double x, double y, double z) : x(x), y(y), z(z) {}

        // unary operators
        Vector operator-() const
        {
            return Vector( -x, -y, -z );
        }
        Vector operator+() const
        {
            return *this;
        }

        // assignment operators
        Vector & operator+=(const Vector &another)
        {
            x += another.x;
            y += another.y;
            z += another.z;
            return *this;
        }
        Vector & operator-=(const Vector &another)
        {
            x -= another.x;
            y -= another.y;
            z -= another.z;
            return *this;
        }

        Vector & operator*=(const double &scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }
        Vector & operator/=(const double &scalar)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        // binary operators
        Vector operator+(const Vector &another) const
        {
            Vector result = *this;
            return result += another;
        }
        Vector operator-(const Vector &another) const
        {
            Vector result = *this;
            return result -= another;
        }

        Vector operator*(const double &scalar) const
        {
            Vector result = *this;
            return result *= scalar;
        }
        Vector operator/(const double &scalar) const
        {
            Vector result = *this;
            return result /= scalar;
        }

        bool operator==(const Vector &another) const
        {
            return equal(x, another.x) && equal(y, another.y) && equal(z, another.z);
        }
        bool operator!=(const Vector &another) const
        {
            return !( *this == another );
        }
        
        // scalar multiplication
        double operator*(const Vector &another) const
        {
            return x*another.x + y*another.y + z*another.z;
        }
        // cross product
        Vector operator&(const Vector &another) const
        {
            return Vector( y*another.z - z*another.y, z*another.x - x*another.z, x*another.y - y*another.x );
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
        Vector & normalize() // normalizes given point/vector in place (!), returns itself
        {
            if( norm() != 0 )
            {
                (*this) /= norm();
            }
            return *this;
        }
        Vector normalized() const  // returns normalized point/vector
        {
            Vector result = *this;
            return result.normalize();
        }

        bool is_zero() const
        {
            return equal(x, 0) && equal(y, 0) && equal(z, 0);
        }
        bool is_collinear_to(const Vector &another) const
        {
            return ((*this) & another).is_zero();
        }
        bool is_orthogonal_to(const Vector &another) const
        {
            return equal( 0, (*this)*another );
        }
    };

    typedef Vector Point; // define an alias

    // more operators
    inline Vector operator*(const double &scalar, const Vector &vector)
    {
        return vector * scalar;
    }
    inline std::ostream &operator<<(std::ostream &stream, const Vector &vector)
    {
        return stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
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

    // triangle class
    class Triangle
    {
    private:
        Point vertices[3];
    public:
        Triangle(const Point &vertex0, const Point &vertex1, const Point &vertex2)
        {
            vertices[0] = vertex0;
            vertices[1] = vertex1;
            vertices[2] = vertex2;
        }
        Point & operator[](unsigned index)
        {
            check( index <= 3, OutOfBoundsError() );
            return vertices[index];
        }
        Point const & operator[](unsigned index) const
        {
            check( index <= 3, OutOfBoundsError() );
            return vertices[index];
        }
        Vector normal() const
        {
            Vector normal = ( (vertices[2] - vertices[0]) & (vertices[1] - vertices[0]) ).normalized(); // normal is calculated as vector product of two sides
            check( !normal.is_zero(), DegeneratedTriangleError() );
            return normal;
        }
    };
};
