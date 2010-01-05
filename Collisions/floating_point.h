#pragma once
#include "assert.h"

namespace Collisions
{
    const __int64 DEFAULT_MAX_ULPS = 50;

    // Helpers for 'proper' comparing floats: assuming equal those, whose
    // difference is less than DEFAULT_MAX_ULPS Units in the Last Place

    // TODO: tests for these functions
    // TODO: user-defined accuracy
    // TODO: re-write using unions
    // TODO: epsilon-comparison near zero

    //
    // the idea from
    // 'Comparing floating point numbers' by Bruce Dawson
    // http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
    //
    inline bool equal(double a, double b)
    {
        assert(sizeof(__int64) == sizeof(double));
        // Make sure maxUlps is non-negative and small enough that the
        // default NAN won't compare as equal to anything.
        assert(DEFAULT_MAX_ULPS > 0 && DEFAULT_MAX_ULPS < 4 * 1024 * 1024); // this is maximum ULPS for floats, for doubles it might be greater, but for what?
        __int64 a_int = *(__int64*)&a;

        double minus_null = -0.0;
        __int64 minus_null_int = *(__int64*)&minus_null;
        // Make a_int lexicographically ordered as a twos-complement int
        if (a_int < 0)
            a_int = minus_null_int - a_int;
        __int64 b_int = *(__int64*)&b;
        // Make b_int lexicographically ordered as a twos-complement int
        if (b_int < 0)
            b_int = minus_null_int - b_int;
       
        __int64 int_diff = _abs64(a_int - b_int);
        if (int_diff <= DEFAULT_MAX_ULPS)
            return true;
        return false;
    }

    inline bool less_or_equal(double a, double b)
    {
        return (a < b) || equal(a, b);
    }

    inline bool greater_or_equal(double a, double b)
    {
        return (a > b) || equal(a, b);
    }
};