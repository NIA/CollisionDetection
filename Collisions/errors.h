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

// a macro for declaring error classes. Don't forget a ';' after it.
#define DECLARE_ERROR(classname, message) \
    class classname : public RuntimeError\
    {\
    public:\
        classname() : RuntimeError( message ) {}\
    }
    
    DECLARE_ERROR( InvalidLineVectorError, "line vector cannot be zero vector" );
    DECLARE_ERROR( InvalidNormalError, "normal cannot be zero vector" );
    DECLARE_ERROR( DegeneratedSegmentError, "segment is degenerated" );
    DECLARE_ERROR( DegeneratedTriangleError, "triangle is degenerated" );
    DECLARE_ERROR( ParallelLinesError, "lines are parallel" );
    DECLARE_ERROR( OutOfBoundsError, "array index out of bounds" );

    template <class ErrType> inline void check( bool should_be_true, const ErrType &error )
    {
        if( ! should_be_true )
            throw error;
    }
};
