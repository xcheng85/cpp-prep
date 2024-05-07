#pragma once

#include <memory>
#include <type_traits>

// two types of type traits
// 1. provide infomation about types: static value member
// 2. type transformation: modify properties of types, static type

// pattern:
// template specialization

// conditional_t
// select type in compile time
namespace core::ctt
{
    // shared_ptr

    // compare to see the value brought by std::false_type (type_traits provided by library)
    // template <typename T>
    // struct is_shared_ptr_impl : std::false_type
    // {
    // };

    namespace impl
    {
        template <typename T>
        struct is_shared_ptr_impl
        {
            static const bool value{false};
        };

        // type specialization
        template <typename T>
        struct is_shared_ptr_impl<std::shared_ptr<T>>
        {
            static const bool value{true};
        };

        // case2: update the property of a type
        // concatenation of two
        // static class member: type::the type referred by T or T if it is not a reference
        // _t: ::type
        template <typename T>
        using remove_cvr_t = std::remove_cv_t<std::remove_reference_t<T>>;

        // unique_ptr
        template <typename T>
        struct is_unique_ptr_impl : std::false_type
        {
        };

        // DeleteFunctor: functor
        template <typename T, typename DeleteFunctor>
        struct is_unique_ptr_impl<std::unique_ptr<T, DeleteFunctor>> : std::true_type
        {
        };
    }

    // a template struct
    template <typename T>
    using is_shared_ptr = impl::is_shared_ptr_impl<impl::remove_cvr_t<T>>;

    // case1: info about the property
    template <typename T>
    constexpr bool is_shared_ptr_v = is_shared_ptr<T>::value;

    template <typename T>
    using is_unique_ptr = impl::is_unique_ptr_impl<impl::remove_cvr_t<T>>;

    template <typename T>
    constexpr bool is_unique_ptr_v = is_unique_ptr<T>::value;

    template <typename T>
    using is_smart_ptr = std::conditional_t<
        is_unique_ptr_v<T>,
        std::true_type,
        std::conditional_t<
            is_shared_ptr_v<T>,
            std::true_type,
            std::false_type>>;

    template <typename T>
    constexpr bool is_smart_ptr_v = is_smart_ptr<T>::value;
}