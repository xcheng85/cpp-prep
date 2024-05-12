#pragma once

#include <memory>
#include <meta.h>

namespace core::container
{
    using namespace core::container::meta;
    using namespace core::utility::meta;

    struct NullParameter
    {
    };

    // Parameters: key
    // Types: hetrogenouse type in the map
    template <typename... Parameters>
    struct HetrogenousMap
    {
        template <typename... Types>
        struct Values
        {
            // Order return the index offset
            // Values + indexOffset == Value type
            template <typename Key>
            using ValueType = At<Values, Order<HetrogenousMap, Key>>;

            // placeholder for non-used key-value pair
            template <typename Key>
            constexpr static bool IsValueNull = std::is_same_v<ValueType<Key>, NullParameter>;

            Values() = default;

            Values(Values &&val)
            {
                for (size_t i = 0; i < sizeof...(Types); ++i)
                {
                    // move shared_ptr
                    _data[i] = std::move(val._data[i]);
                }
            }

            Values(const Values &) = default;
            Values &operator=(const Values &) = default;
            Values &operator=(Values &&) = default;

            Values(std::shared_ptr<void> (&&input)[sizeof...(Types)])
            {
                for (size_t i = 0; i < sizeof...(Types); ++i)
                {
                    _data[i] = std::move(input[i]);
                }
            }

            template <typename Key>
            const auto &Get() const
            {
                constexpr static auto KeyIndexOffset = Order<HetrogenousMap, Key>;
                using ValueType = At<Values, KeyIndexOffset>;

                // raw pointer from shared pointer
                void *tmp = _data[KeyIndexOffset].get();
                if (!tmp)
                {
                    throw std::runtime_error("Empty Value.");
                }
                // meta exists and type cast
                ValueType *res = static_cast<ValueType *>(tmp);
                return *res;
            }

            template <typename Key>
            auto &Get()
            {
                constexpr static auto KeyIndexOffset = Order<HetrogenousMap, Key>;
                using ValueType = At<Values, KeyIndexOffset>;

                void *tmp = _data[KeyIndexOffset].get();
                if (!tmp)
                {
                    throw std::runtime_error("Empty Value.");
                }

                ValueType *res = static_cast<ValueType *>(tmp);
                return *res;
            }

            // &&: allow rvalue caller
            template <typename Key, typename Value>
            auto SetKV(Value &&val) &&
            {
                constexpr static auto KeyIndexOffset = Order<HetrogenousMap, Key>;
                // custom type traits
                using RawValue = RemConstRef<Value>;
                // let share_ptr to manage it
                RawValue *tmp = new RawValue(std::forward<Value>(val));
                // custom deleter
                _data[KeyIndexOffset] = std::shared_ptr<void>(tmp,
                                                              [](void *ptr)
                                                              {
                                                                  RawValue *typedPtr = static_cast<RawValue *>(ptr);
                                                                  delete typedPtr;
                                                              });

                if constexpr (std::is_same_v<RawValue, At<Values, KeyIndexOffset>>)
                {
                    return *this;
                }
                else
                {
                    using new_type = Set<Values, KeyIndexOffset, RawValue>;
                    return new_type(std::move(_data));
                }
            }

        private:
            // void will be recast.
            // void*
            std::shared_ptr<void> _data[(sizeof...(Types) == 0) ? 1 : sizeof...(Types)];
        };

    public:
        static auto Create()
        {
            using type = meta::Create<Values, NullParameter, sizeof...(Parameters)>;
            return type{};
        }
    };
}