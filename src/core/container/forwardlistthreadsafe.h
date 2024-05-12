#pragma once

#include <optional>
#include <memory>
#include <logger.h>

namespace core::container
{
    using namespace core::utility;

    template <typename T>
    class ForwardListThreadSafe
    {
    public:
        struct DListNode
        {
            std::shared_ptr<DListNode> prev;
            std::shared_ptr<DListNode> next;
            std::optional<T> val;
            std::mutex mux;

            ~DListNode()
            {
                DefaultLogger::Instance().info("~DListNode");
            }
        };

        // Iterator for custom class to support the for-range based loop
        class Iterator
        {
        public:
            Iterator(std::shared_ptr<DListNode> node) : _pNode{node}
            {
                DefaultLogger::Instance().info("Iterator");
            }
            // prefix increment operator
            Iterator &operator++()
            {
                _pNode = _pNode->next;
                return *this;
            }
            // Postfix increment operator
            Iterator operator++(int)
            {
                Iterator temp = *this;
                ++*this;
                return temp;
            }

            bool operator!=(const Iterator &other) const
            {
                return _pNode.get() != other._pNode.get();
            }

            const DListNode &operator*() const
            {
                return *_pNode;
            }

        private:
            std::shared_ptr<DListNode> _pNode;
        };

        DListThreadSafe()
        {
            _head = std::make_shared<DListNode>();
            _tail = std::make_shared<DListNode>();
            _head->next = _tail;
            _tail->prev = _head;
        }

        // push_back, push_front
        // lock the last node, the tail and
        void push_back(const T &value)
        {
            DefaultLogger::Instance().info(format("push_back: {}", value));
            auto &lastNode = _tail->prev;
            auto newNode = std::make_shared<DListNode>();

            std::scoped_lock lock{lastNode->mux, newNode->mux, _tail->mux};
            lastNode->next = newNode;
            newNode->next = _tail;
            newNode->prev = lastNode;
            newNode->val = value;
            _tail->prev = newNode;
        }

        // easy to break in the multi-thread context,
        // return the iterator to the consumer and iterator may be stale later.
        Iterator begin() const { return Iterator(_head->next); }
        Iterator end() const { return Iterator(_tail); }

        const Iterator cbegin() const { return Iterator(_head->next); }
        const Iterator cend() const { return Iterator(_tail); }

    private:
        std::shared_ptr<DListNode> _head{nullptr};
        std::shared_ptr<DListNode> _tail{nullptr};
    };
}