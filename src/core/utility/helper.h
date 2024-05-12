#pragma once

#include <type_traits>

namespace core::utility::meta
{
    template <typename T>
    using RemConstRef = std::remove_cv_t<std::remove_reference_t<T>>;

    template <auto N>
    struct Int_
    {
        constexpr static auto value = N;
    };

    template <int... I>
    struct IndexSequence;

    template <typename L, typename R>
    struct ConcatSequence;

    // just for the compile types
    template <int... L, int... R>
    struct ConcatSequence<IndexSequence<L...>, IndexSequence<R...>>
    {
        using type = IndexSequence<L..., (R + sizeof...(L))...>;
    };

    template <int N>
    struct MakeIndexSequence_
    {
        // recursive
        using type = typename ConcatSequence<
            typename MakeIndexSequence_<N / 2>::type,
            typename MakeIndexSequence_<N - N / 2>::type>::type;
    };

    template <>
    struct MakeIndexSequence_<1>
    {
        using type = IndexSequence<0>;
    };

    template <>
    struct MakeIndexSequence_<0>
    {
        using type = IndexSequence<>;
    };

    template <int N>
    using MakeIndexSequence = typename MakeIndexSequence_<N>::type;
    // =========================================================================================

    // KVBinder ================================================================================
    template <typename TK, typename TV>
    struct KVBinder
    {
        using KeyType = TK;
        using ValueType = TV;
        static TV apply(TK *);
    };

    template <bool b>
    struct When;
}
