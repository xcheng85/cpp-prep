#pragma once

#include <initializer_list>
#include <shared.h>

namespace Functions
{
    void testFunctionVaringParameters(std::initializer_list<int> params)
    {
        // support forrange loop due to its implementation of following
        // begin return first iterator
        // end return last itr
        // extension through function overload, Open-Close Principle
        // std::begin  (ACL)
        // std::end

        LOG_I_ITRABLE(params);
    }

    // function rvalue passed in non-const referecne
    template<typename T>
    void testNonConstRvalueReference(T& ) {

    }
}