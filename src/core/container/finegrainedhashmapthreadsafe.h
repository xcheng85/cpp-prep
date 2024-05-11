#pragma once

#include <optional>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>
#include <shared_mutex> //after c++17
#include <mutex>        //after c++11
#include <list>         // for separate chaining
#include <algorithm>    //find_if
#include <logger.h>

namespace core::container
{
    using namespace core::utility;

    // map
    // sorted array: cannot fine-grained lock
    // red-black tree: cannot fined-grained lock

    // hashmap
    // bucket-wise lock: fine grained

    // template<
    //     class Key,
    //     class T,
    //     class Hash = std::hash<Key>,
    //     class KeyEqual = std::equal_to<Key>,
    //     class Allocator = std::allocator<std::pair<const Key, T>>
    // > class unordered_map;

    // forward-declaration with default template parameters;
    template <typename Key, typename T, typename Hash = std::hash<Key>>
    class FineGrainedHashMapThreadSafe;

    template <typename Key, typename T>
    class SeparateChaining
    {
    public:
        std::optional<T> value(const Key &key) const
        {
            std::optional<T> res;
            // readonly use shared_lock
            std::shared_lock lock{_mutex};
            const auto itr = iteratorByKey(key);
            if (itr == _data.end())
            {
                return res;
            }
            else
            {
                res = itr->second;
                return res;
            }
        }

        void setVal(const Key &key, const T &value)
        {
            std::scoped_lock lock{_mutex};
            auto itr = iteratorByKey(key);
            if (itr == _data.end())
            {
                _data.emplace_back(std::make_pair(
                    key, value));
            }
            else
            {
                itr->second = value;
            }
        }

        void del(const Key &key)
        {
            std::scoped_lock lock{_mutex};
            const auto itr = iteratorByKey(key);
            if (itr != _data.end())
            {
                _data.erase(itr);
            }
        }

        friend class FineGrainedHashMapThreadSafe<Key, T>;

    private:
        // linked-list chaining
        // for the non-const caller
        using Node = std::pair<Key, T>;
        std::list<Node>::iterator iteratorByKey(const Key &key)
        {
            return std::find_if(std::begin(_data), std::end(_data), [&](auto &node)
                                {
                // key must support operator==
                return node.first == key; });
        }
        // for the const caller
        std::list<Node>::const_iterator iteratorByKey(const Key &key) const
        {
            return std::find_if(std::begin(_data), std::end(_data), [&](auto &node)
                                {
                // key must support operator==
                return node.first == key; });
        }

        // multiple read and single write
        mutable std::shared_mutex _mutex;
        std::list<Node> _data; // data to be protected
    };

    template <typename Key, typename T, typename Hash>
    class FineGrainedHashMapThreadSafe
    {
    public:
        FineGrainedHashMapThreadSafe(size_t numBuckets = 20, const Hash &hasher = Hash())
            : _hasher{hasher}, _buckets(numBuckets)
        {
            for (size_t i = 0; i < numBuckets; ++i)
            {
                _buckets[i].reset(new SeparateChaining<Key, T>());
            }
        }
        FineGrainedHashMapThreadSafe(const FineGrainedHashMapThreadSafe &) = delete;
        FineGrainedHashMapThreadSafe &operator=(const FineGrainedHashMapThreadSafe &) = delete;

        void setVal(const Key &key, const T &value)
        {
            auto &chain = bucketChain(key);
            return chain.setVal(key, value);
        }

        std::optional<T> value(const Key &key) const
        {
            const auto &chain = bucketChain(key);
            return chain.value(key);
        }

        void del(const Key &key)
        {
            auto &chain = bucketChain(key);
            return chain.del(key);
        }

        // snapshot peek
        std::unordered_map<Key, T> peek() const
        {
            std::unordered_map<Key, T> res;
            // lock all the bucket
            // unique_lock: Transfer of ownership (being moveable).
            // scoped_lock: not movable
            std::vector<std::unique_lock<std::shared_mutex>> locks;
            for (size_t i = 0; i < _buckets.size(); ++i)
            {
                locks.emplace_back(_buckets[i]->_mutex);
            }
            for (size_t i = 0; i < _buckets.size(); ++i)
            {
                for (auto itr = _buckets[i]->_data.begin(); itr != _buckets[i]->_data.end(); ++itr)
                {
                    // pair
                    res.insert(*itr);
                }
            }
            return res;
        }

    private:
        auto &bucketChain(const Key &key)
        {
            const auto bucketIdx = _hasher(key) % _buckets.size();
            return *(_buckets[bucketIdx]);
        }
        // for const caller
        const auto &bucketChain(const Key &key) const
        {
            const auto bucketIdx = _hasher(key) % _buckets.size();
            return *(_buckets[bucketIdx]);
        }

        Hash _hasher;
        mutable std::vector<std::unique_ptr<SeparateChaining<Key, T>>> _buckets;
    };
}