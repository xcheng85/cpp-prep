#pragma once

#include <shared.h>

namespace Memory
{
    struct Player
    {
        Player()
        {
            LOG_I("player ctor");
        }

        Player(const Player &other) noexcept
        {
            LOG_I("player copy ctor");
        }
        Player &operator=(const Player &other) noexcept
        {
            LOG_I("player operator=");
            return *this;
        }
        Player(Player &&other) noexcept
        {
            LOG_I("player copy ctor");
        }
        Player &operator=(Player &&other) noexcept
        {
            LOG_I("player operator= rvalue");
            return *this;
        }
        ~Player()
        {
            LOG_I("player dtor")
        }
    };

    void testAutoCastawayConstRef()
    {
        Player p1;
        // no copy
        const auto &p2 = p1;
        // cast away the const auto& from p2;
        // have copy
        auto p3 = p2;
    }

    void testAutoNotCastawayConstRef()
    {
        Player p1;
        // no copy
        const auto &p2 = p1;
        // cast away the const auto& from p2;
        // have copy
        decltype(auto) p3 = p2;
    }
}