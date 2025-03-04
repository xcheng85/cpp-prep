#include <string>
#include <bridge.h>

namespace Bridge
{
    struct Player::Impl
    {
        std::string first;
        std::string last;
        int number;
        // a lot of default ctor,
    };
    Player::Player()
        : _pimp(std::make_unique<Impl>())
    {
    }

    Player::Player(const Player &other)
        : _pimp(std::make_unique<Impl>(*other._pimp)) // default copy ctor of impl
    {
    }

    Player &Player::operator=(const Player &other)
    {
        *_pimp = *other._pimp;
        return *this;
    }

    Player::Player(Player &&other) noexcept
        : _pimp(std::make_unique<Impl>(std::move(*other._pimp)))
    {
    }

    Player &Player::operator=(Player &&other) noexcept
    {
        *_pimp = std::move(*other._pimp);
        return *this;
    }

    int Player::number() const
    {
        return _pimp->number;
    }
}