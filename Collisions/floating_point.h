#pragma once
#include "assert.h"

// Helpers for 'proper' comparing floating point numbers: assuming equal those ones,
// whose difference is less than given max_ulps Units in the Last Place

namespace Collisions
{
    union DoubleAndInt
    {
        double double_;
        __int64 int_;
    };

    const __int64 DEFAULT_MAX_ULPS = 50;

    // TODO: tests for these functions
    // TODO: epsilon-comparison near zero

    //
    // the idea from
    // 'Comparing floating point numbers' by Bruce Dawson
    // http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
    //
    inline bool equal(double a, double b, __int64 max_ulps = DEFAULT_MAX_ULPS)
    {
        assert(sizeof(__int64) == sizeof(double));
        // Make sure max_ulps is non-negative and small enough that the
        // default NAN won't compare as equal to anything.
        assert(max_ulps > 0 && max_ulps < 4 * 1024 * 1024); // this is maximum ULPS for floats, for doubles it might be greater, but for what?
        
        
        DoubleAndInt a_union = { a };
        DoubleAndInt b_union = { b };
        
        __int64 a_int = a_union.int_;
        __int64 b_int = b_union.int_;

        DoubleAndInt minus_null_union = { -0.0 };
        __int64 minus_null_int = minus_null_union.int_;
        // Make a_int lexicographically ordered as a twos-complement int
        if (a_int < 0)
            a_int = minus_null_int - a_int;
        // Make b_int lexicographically ordered as a twos-complement int
        if (b_int < 0)
            b_int = minus_null_int - b_int;
       
        __int64 int_diff = _abs64(a_int - b_int);
        if (int_diff <= max_ulps)
            return true;

        return false;
    }

    inline bool less_or_equal(double a, double b, __int64 max_ulps = DEFAULT_MAX_ULPS)
    {
        return (a < b) || equal(a, b, max_ulps);
    }

    inline bool greater_or_equal(double a, double b, __int64 max_ulps = DEFAULT_MAX_ULPS)
    {
        return (a > b) || equal(a, b, max_ulps);
    }
};
