#pragma once
#include <cstring>
#include <vector>
#include <typeinfo>
#include <string_view>
#include <thread>
#include <chrono>

#include <shared.h>
namespace Strings
{
    using namespace std::string_literals;
    using namespace std::chrono_literals;
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

        std::vector players{"Giannis"};
        std::vector players2{"Giannis"s};
        // [Argument Deduction for c str]: St6vectorIPKcSaIS1_EE
        LOG_TRACE_I("Argument Deduction for c str", typeid(players).name());
        // St6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE
        LOG_TRACE_I("Argument Deduction for std str", typeid(players2).name());
    }

    // value of string_view
    // disallow rvalue
    void testBeforeStringViewRvalue(std::string &s)
    {
        LOG_TRACE_I("testBeforeStringView"s, s);
    }

    void testAfterStringView(std::string_view sv)
    {
        LOG_TRACE_I("testAfterStringView"s, sv);
    }

    void testStringViewDanglingPtr(std::string_view sv)
    {
        std::this_thread::sleep_for(1s);
        // and the caller will release the string behind sv
        LOG_TRACE_I("testStringViewDanglingPtr"s, sv);
    }
}