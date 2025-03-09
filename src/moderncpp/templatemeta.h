#pragma once
#include <stddef.h>
#include <array>
#include <vector>
#include <iostream>
#include <cassert>

#include <shared.h>
#include <concepts>

namespace TemplateMeta
{
    // T: template type parameter
    // size_t N: non-type template parameter
    // template template parameter
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
        // function template as friends of class templates
        // so it can access _data
        // don't forget <T, N>
        friend Vec operator+ <T, N>(const Vec &v1, const Vec &v2);

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

    template <typename T, size_t N>
    Vec<T, N> operator+(const Vec<T, N> &v1, const Vec<T, N> &v2)
    {
        std::array<T, N> res;
        for (int i = 0; i < N; i++)
        {
            res[i] = v1._data[i] + v2._data[i];
        }
        return Vec<T, N>(res);
    }

    using Vec2i = Vec<int, 2>;

    void testTemplateMeta()
    {
        // array literal
        TemplateMeta::Vec2i v1({1, 2});
        TemplateMeta::Vec2i v2({-1, -2});
        LOG_I(v1.size());
        LOG_I(v1);

        auto v3 = v1 + v2;
        LOG_I(v3);
    }

    // template recursion to build matrix N x N
    // base class
    // 1d texture
    // 2d texture
    // 3d texture 512 * 512 * 512

    // N: 1, 2, 3
    template <typename T, size_t N>
    class TextureND
    {
    public:
        TextureND() = delete;
        // 64, 128, 256, ...
        explicit TextureND(size_t size)
        {
            LOG_I(std::format("TextureND({}): ctor", N));
            _data.resize(size, TextureND<T, N - 1>(size));
        }

        // accessor
        const TextureND<T, N - 1> &operator[](size_t i) const
        {
            return _data[i];
        }

    private:
        // 1d memory though in gpu
        // cannot use array due to dim is not known in compile-time.
        std::vector<TextureND<T, N - 1>> _data;
    };

    // partial template
    template <typename T>
    class TextureND<T, 1>
    {
    public:
        TextureND() = delete;
        // 64, 128, 256, ...
        explicit TextureND(size_t size)
        {
            LOG_I(std::format("TextureND({}): ctor", 1));
            _data.resize(size);
        }

        // accessor
        const std::vector<T> &operator[](size_t i) const
        {
            return _data[i];
        }

    private:
        // 1d memory though in gpu
        // cannot use array due to dim is not known in compile-time.
        std::vector<T> _data;
    };

    using Texture2Df = TextureND<float, 2>;
    using Texture3Df = TextureND<float, 3>;

    void testTemplateRecursiveClass()
    {
        // array literal
        Texture2Df t1(128);
    }
}