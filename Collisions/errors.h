#pragma once
#include <exception>

namespace Collisions
{
    class RuntimeError : public std::exception
    {
    private:
        const char *message;
    public:
        RuntimeError( const char *message = "runtime error" ) : message( message ) {}
        virtual const char *what() const throw() { return message; }
    };

    // TODO: generator

    class InvalidLineVectorError : public RuntimeError
    {
    public:
        InvalidLineVectorError() : RuntimeError( "line vector cannot be zero vector" ) {}
    };

    class InvalidNormalError : public RuntimeError
    {
    public:
        InvalidNormalError() : RuntimeError( "normal cannot be zero vector" ) {}
    };

    class DegeneratedSegmentError : public RuntimeError
    {
    public:
        DegeneratedSegmentError() : RuntimeError( "segment is degenerated" ) {}
    };

    class DegeneratedTriangleError : public RuntimeError
    {
    public:
        DegeneratedTriangleError() : RuntimeError( "triangle is degenerated" ) {}
    };

    class ParallelLinesError : public RuntimeError
    {
    public:
        ParallelLinesError() : RuntimeError( "lines are parallel" ) {}
    };

    template <class ErrType> inline void check( bool should_be_true, const ErrType &error )
    {
        if( ! should_be_true )
            throw error;
    }
};
