#pragma once

#include <iostream>
#include <limits>
#include <shared.h>


namespace BasicTypes
{
    inline void testBasicTypes()
    {
        LOG_I(sizeof(double));      // some compilers print 8
        LOG_I(sizeof(long double)); // some compilers print 16
    }

    inline void testBasicTypeLimits()
    {
        LOG_I(std::numeric_limits<int>::min());
        LOG_I(std::numeric_limits<int>::max());
        // 0
        LOG_I(std::numeric_limits<float>::min());
        LOG_I(-std::numeric_limits<float>::max());
        // same as previous line
        LOG_I(std::numeric_limits<float>::lowest());
        // 0
        LOG_I(std::numeric_limits<double>::min());
        // 0
        LOG_I(std::numeric_limits<long double>::min());
    }
}
