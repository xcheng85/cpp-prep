#pragma once

#include <optional>
#include <memory>
#include <map>
#include <logger.h>
#include <shared_mutex> //after c++17
#include <mutex>        //after c++11

namespace core::container
{
    using namespace core::utility;

    template <typename K, typename V>
    class MapThreadSafe
    {
    public:
        void set(const K &key, const V &value)
        {
            // use normal lock
            std::scoped_lock lock{_mux};
            _container[key] = value;
        }

        std::optional<V> get(const K &key)
        {
            std::optional<V> res;
            std::shared_lock lock{_mux};
            if (_container.count(key) == 1)
            {
                return _container.at(key);
            } 
            return res;
        }

    private:
        std::map<K, V> _container;
        mutable std::shared_mutex _mux; // due to line 27
    };
}