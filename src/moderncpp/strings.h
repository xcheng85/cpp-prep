#pragma once
#include <cstring>
#include <vector>
#include <shared.h>
#include <typeinfo>

namespace Strings
{
    void testCString()
    {
        const char str[]{"Dame"};
        LOG_I(str);
        // strlen does not consider the null terminator
        LOG_TRACE_I("strlen", strlen(str));
        // including the null terminator
        LOG_TRACE_I("sizeof", sizeof(str));
        //
        const auto p = str;
        // 8 bytes * 8 = 64 bit
        LOG_TRACE_I("sizeof ptr (bytes)", sizeof(p));
    }

    void testClassTemplateArgumentDeduction()
    {
        using namespace std::string_literals;

        std::vector players{"Giannis"};
        std::vector players2{"Giannis"s};
        // [Argument Deduction for c str]: St6vectorIPKcSaIS1_EE
        LOG_TRACE_I("Argument Deduction for c str", typeid(players).name());
        // St6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE
        LOG_TRACE_I("Argument Deduction for std str", typeid(players2).name());
    }
}