#pragma once

#include <array>
#include <iostream>
#include <format>

namespace Entity
{
    class IpAddress
    {
    public:
        IpAddress() = delete;
        explicit IpAddress(
            unsigned char a1,
            unsigned char a2,
            unsigned char a3,
            unsigned char a4)
            : _ip{a1, a2, a3, a4}
        {
        }
        // 32, bit mask
        explicit IpAddress(unsigned int a)
            : _ip{
                  static_cast<unsigned char>((a >> 24) & 0xFF),
                  static_cast<unsigned char>((a >> 16) & 0xFF),
                  static_cast<unsigned char>((a >> 8) & 0xFF),
                  static_cast<unsigned char>(a & 0xFF),
              }
        {
        }

        // copy ctor
        // noexcept: stl container avoid copy for move
        IpAddress(const IpAddress &other)
        {
            _ip = other._ip;
            return;
        }
        // operator overload
        IpAddress &operator=(const IpAddress &other)
        {
            _ip = other._ip;
            return *this;
        }
        // move assignment
        IpAddress(const IpAddress &&other) noexcept
        {
            // don't forget this precaution check
            if (this == &other)
            {
                return;
            }
            _ip = std::move(other._ip);
            return;
        }
        IpAddress &operator=(const IpAddress &&other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }
            _ip = std::move(other._ip);
            return *this;
        }

        bool operator<=(const IpAddress&other) noexcept
        {
            // bit packing
            return packing() <= other.packing();
        }
        // prefix
        IpAddress& operator++() noexcept
        {
            // bit packing
            // use unpacking ctor
            *this = IpAddress(packing() + 1);
            return *this;
        }
        //postfix
        IpAddress& operator++(int) noexcept
        {
            ++(*this);
            return *this;
        }
        // needed for class not for structure
        friend std::ostream &operator<<(std::ostream &os, const IpAddress &ipAddr);
        friend std::istream &operator>>(std::istream &is, IpAddress &ipAddr);

    protected:
        const unsigned int packing() const noexcept
        {
            return (static_cast<unsigned int>(_ip[0]) << 24) |
                   (static_cast<unsigned int>(_ip[1]) << 16) |
                   (static_cast<unsigned int>(_ip[2]) << 8) |
                   static_cast<unsigned int>(_ip[3]);
        }

    private:
        // [0, 255]
        std::array<unsigned char, 4> _ip;
    };

    // global io for IpAddress
    std::ostream &operator<<(std::ostream &os, const IpAddress &ipAddr)
    {
        const auto s = std::format("{}.{}.{}.{}\n", ipAddr._ip[0], ipAddr._ip[1],
                                   ipAddr._ip[2], ipAddr._ip[3]);
        os << s;
        return os;
    }
    // no-const, it is a writable action
    std::istream &operator>>(std::istream &is, IpAddress &ipAddr)
    {
        char delimeter[3];
        int a[4];

        is >> a[0] >> delimeter[0] >> a[1] >> delimeter[1] >> a[2] >> delimeter[2] >> a[3];
        if (delimeter[2] == delimeter[1] && delimeter[1] == delimeter[0] && delimeter[0] == '.')
        {
            ipAddr._ip[3] = a[3];
            ipAddr._ip[2] = a[2];
            ipAddr._ip[1] = a[1];
            ipAddr._ip[0] = a[0];
        }
        else
        {
            // such as int j,
            // cin >> j; // input is not number, behind scene is.set error state
            is.setstate(std::ios_base::failbit);
        }

        return is;
    }
};