#pragma once
#include <stddef.h>
#include <array>
#include <iostream>
#include <cassert>

#include <shared.h>

namespace TemplateMeta
{
    template <typename T, size_t N>
    class Vec
    {
    public:
        Vec() = delete;
        // support rvalue
        explicit Vec(const std::array<T, N> &v)
            : _data{v}
        {
        }

        ~Vec() = default;

        Vec(const Vec &other) noexcept = default;
        Vec(Vec &&other) noexcept = default;
        Vec &operator=(const Vec &other) noexcept = default;
        Vec &operator=(Vec &other) noexcept = default;

        static constexpr size_t size()
        {
            return N;
        }
        // operator
        const T &operator[](size_t i) const
        {
            assert(i < N);
            return _data[i];
        }

        T &operator[](size_t i)
        {
            assert(i < N);
            return _data[i];
        }

    private:
        std::array<T, N> _data;
    };

    template <typename T, size_t N>
    std::ostream &operator<<(std::ostream &os, const Vec<T, N> &v)
    {
        os << "[";
        for (int i = 0; i < N - 1; i++)
        {
            os << v[i] << ", ";
        }
        os << v[N - 1] << "]" << std::endl;
        return os;
    }

    using Vec2i = Vec<int, 2>;

    void testTemplateMeta()
    {
        // array literal
        TemplateMeta::Vec2i v({1, 2});
        LOG_I(v.size());
        LOG_I(v);
    }
}