#pragma once

#include <memory>
#include <helper.h>

namespace core::container::meta
{
    using namespace core::utility::meta;
    namespace ConcatContainer
    {
        template <typename L, typename R>
        struct Concat;

        template <template <typename...> typename Container, typename... L, typename... R>
        struct Concat<Container<L...>, Container<R...>>
        {
            using type = Container<L..., R...>;
        };
    }

    template <template <typename...> typename Container, typename Param, int N>
    struct Create_
    {
        using type = typename ConcatContainer::Concat<
            typename Create_<Container, Param, N / 2>::type,
            typename Create_<Container, Param, N - N / 2>::type>::type;
    };

    template <template <typename...> typename Container, typename Param>
    struct Create_<Container, Param, 1>
    {
        using type = Container<Param>;
    };

    template <template <typename...> typename Container, typename Param>
    struct Create_<Container, Param, 0>
    {
        using type = Container<>;
    };

    template <template <typename...> typename Container, typename Param, int N>
    using Create = typename Create_<Container, Param, N>::type;

    namespace AtImpl
    {
        template <typename ignore>
        struct impl;

        template <int... ignore>
        struct impl<IndexSequence<ignore...>>
        {
            template <typename nth>
            static nth apply(decltype(ignore, (void *)nullptr)..., nth *, ...);
        };
    }

    template <typename Container, int N>
    struct At_;

    template <template <typename...> typename Container, typename... Params, int N>
    struct At_<Container<Params...>, N>
    {
        using type = decltype(AtImpl::impl<MakeIndexSequence<N>>::apply((Params *)nullptr...));
    };

    template <typename Container, int N>
    using At = typename At_<Container, N>::type;

    namespace OrderImpl
    {
        template <typename Index, typename Container>
        struct impl;

        // kvbinder: bind type with its index in the container
        template <template <typename...> typename Container, typename... Types, int... index>
        struct impl<IndexSequence<index...>, Container<Types...>>
            : KVBinder<Types, Int_<index>>...
        {
            using KVBinder<Types, Int_<index>>::apply...;
        };
    }

    template <typename Container, typename Request>
    struct Order_;

    template <template <typename...> typename Container, typename... Params, typename Request>
    struct Order_<Container<Params...>, Request>
    {
        using IndexSeq = MakeIndexSequence<sizeof...(Params)>;
        // retrieve the offset index from the request Type
        using LookUpTable = OrderImpl::impl<IndexSeq, Container<Params...>>;

        using IndexOffsetType = decltype(LookUpTable::apply((Request *)nullptr));
        constexpr static int value = IndexOffsetType::value;
    };

    template <typename Container, typename Request>
    constexpr static int Order = Order_<Container, Request>::value;

    // Set ====================================================================================
    namespace SetImpl
    {
        template <typename TCon, int N, typename TValue, typename TRemain, typename = When<true>>
        struct imp_;

        template <template <typename...> typename TCon, int N, typename TValue, typename... TProcessed, typename T0, typename... TRemain>
        struct imp_<TCon<TProcessed...>, N, TValue, TCon<T0, TRemain...>, When<(N == 0)>>
        {
            using type = TCon<TProcessed..., TValue, TRemain...>;
        };

        template <template <typename...> typename TCon, int N, typename TValue,
                  typename... TProcessed, typename T0, typename T1, typename... TRemain>
        struct imp_<TCon<TProcessed...>, N, TValue, TCon<T0, T1, TRemain...>, When<(N == 1)>>
        {
            using type = TCon<TProcessed..., T0, TValue, TRemain...>;
        };

        template <template <typename...> typename TCon, int N, typename TValue,
                  typename... TProcessed, typename T0, typename T1, typename T2, typename... TRemain>
        struct imp_<TCon<TProcessed...>, N, TValue, TCon<T0, T1, T2, TRemain...>, When<(N == 2)>>
        {
            using type = TCon<TProcessed..., T0, T1, TValue, TRemain...>;
        };

        template <template <typename...> typename TCon, int N, typename TValue,
                  typename... TProcessed,
                  typename T0, typename T1, typename T2, typename T3, typename... TRemain>
        struct imp_<TCon<TProcessed...>, N, TValue, TCon<T0, T1, T2, T3, TRemain...>, When<(N == 3)>>
        {
            using type = TCon<TProcessed..., T0, T1, T2, TValue, TRemain...>;
        };

        template <template <typename...> typename TCon, int N, typename TValue,
                  typename... TProcessed,
                  typename T0, typename T1, typename T2, typename T3, typename... TRemain>
        struct imp_<TCon<TProcessed...>, N, TValue, TCon<T0, T1, T2, T3, TRemain...>, When<(N >= 4) && (N < 8)>>
        {
            using type = typename imp_<TCon<TProcessed..., T0, T1, T2, T3>,
                                       N - 4, TValue, TCon<TRemain...>>::type;
        };

        template <template <typename...> typename TCon, int N, typename TValue,
                  typename... TProcessed,
                  typename T0, typename T1, typename T2, typename T3,
                  typename T4, typename T5, typename T6, typename T7,
                  typename... TRemain>
        struct imp_<TCon<TProcessed...>, N, TValue,
                    TCon<T0, T1, T2, T3, T4, T5, T6, T7, TRemain...>, When<(N >= 8) && (N < 16)>>
        {
            using type = typename imp_<TCon<TProcessed..., T0, T1, T2, T3, T4, T5, T6, T7>,
                                       N - 8, TValue, TCon<TRemain...>>::type;
        };

        template <template <typename...> typename TCon, int N, typename TValue,
                  typename... TProcessed,
                  typename T0, typename T1, typename T2, typename T3,
                  typename T4, typename T5, typename T6, typename T7,
                  typename T8, typename T9, typename TA, typename TB,
                  typename TC, typename TD, typename TE, typename TF,
                  typename... TRemain>
        struct imp_<TCon<TProcessed...>, N, TValue,
                    TCon<T0, T1, T2, T3, T4, T5, T6, T7,
                         T8, T9, TA, TB, TC, TD, TE, TF,
                         TRemain...>,
                    When<(N >= 16)>>
        {
            using type = typename imp_<TCon<TProcessed...,
                                            T0, T1, T2, T3, T4, T5, T6, T7,
                                            T8, T9, TA, TB, TC, TD, TE, TF>,
                                       N - 16, TValue, TCon<TRemain...>>::type;
        };
    }

    template <typename TCont, int N, typename TValue>
    struct Set_;

    template <template <typename...> typename TCont, int N, typename TValue, typename... TParams>
    struct Set_<TCont<TParams...>, N, TValue>
    {
        using type = typename SetImpl::imp_<TCont<>, N, TValue, TCont<TParams...>>::type;
    };

    template <typename TCont, int N, typename TValue>
    using Set = typename Set_<TCont, N, TValue>::type;
}