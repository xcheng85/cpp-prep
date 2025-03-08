#pragma once

#include <shared.h>

namespace Enums
{
    namespace OldStyle
    {
        // old style enum
        enum POSITION : int
        {
            PG = 1,
            SG = 2,
            SF = 3,
            PF = 4,
            C = 5
        };

        enum TEAM : int
        {
            ATLANTA = 1,
            BULLS = 2,
            BUCKS = 3,
            ROCKETS = 4,
        };
    }

    // only difference is class
    namespace NewStyle
    {
        // old style enum
        enum class POSITION : int
        {
            PG = 1,
            SG = 2,
            SF = 3,
            PF = 4,
            C = 5
        };

        enum class TEAM : int
        {
            ATLANTA = 1,
            BULLS = 2,
            BUCKS = 3,
            ROCKETS = 4,
        };
    }


    void testEnumOld()
    {
        using namespace OldStyle;
        auto pos = POSITION::PG;
        auto team = TEAM::ATLANTA;
        // all implicit to integer
        if (pos == team) // no problem (bad)
        {
            LOG_E("bad");
        }
    }

     void testEnumNew()
    {
        using namespace NewStyle;
        auto pos = POSITION::PG;
        auto team = TEAM::ATLANTA;
        // compiler could not pass, good
        // if (pos == team) // no problem (bad)
        // {
        //     LOG_E("bad");
        // }
    }
}