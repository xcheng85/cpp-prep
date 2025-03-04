#pragma once

#include <memory>

namespace Bridge
{
    class Player
    {
    public:
        // must be in separate cpp, due to hide definition of impl
        Player();
        ~Player() = default;
        Player(const Player &);
        Player &operator=(const Player &);

        Player(Player &&) noexcept;
        Player &operator=(Player &&) noexcept;

        int number() const;

    private:
        // forward declaration
        struct Impl;
        std::unique_ptr<Impl> _pimp;
    };
}