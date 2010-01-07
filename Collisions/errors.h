#pragma once
#include <exception>

namespace Collisions
{
    class RuntimeError : public std::exception
    {
    public:
        RuntimeError( const char *message = "runtime error" ) : std::exception( message ) {}
    };

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

    template <class ErrType> inline void check( bool should_be_true, const ErrType &error )
    {
        if( ! should_be_true )
            throw error;
    }
};
