#pragma once

#include <memory>
#include <shared.h>

namespace SmartPointers
{
    // with customDeleter, c-style database
    // for example:
    // vkCreateCommandPool
    // vkDestroyCommandPool

    // functor for create buffer
    //

    struct VkCommandPool : public std::enable_shared_from_this<VkCommandPool>
    {
        VkCommandPool()
        {
            LOG_I("VkCommandPool::ctor");
        }

        ~VkCommandPool()
        {
            LOG_I("VkCommandPool::dtor");
        }

        std::shared_ptr<VkCommandPool> getptr()
        {
            return shared_from_this();
        }
    };
    using VkCommandPoolPtr = VkCommandPool *;

    // T represent vulkan object ptr: VkCommandPoolPtr
    template <typename T>
    class vkCreateObjectHandle
    {
    public:
        T *operator()() const
        {
            // MIMIC VULKAN
            return new T;
        }
    };

    // class vkDestroyObjectHandle
    // {
    // public:
    //     template <typename T>
    //     void operator()(T *object) const
    //     {
    //         // MIMIC VULKAN
    //         delete object;
    //     }
    // };

    // template <auto fn>
    struct vkDestroyObjectHandle
    {
        template <typename T>
        constexpr void operator()(T *arg) const
        {
            // fn(arg);
        }
    };

    // template <typename T>
    // using vkUniquePtr = std::unique_ptr<T, vkDestroyObjectHandle>;

    //     template<typename T>
    // using deleted_unique_ptr = std::unique_ptr<T,std::function<void(T*)>>;

    // using VkCommandPoolUniquePointer =
    //     std::unique_ptr<VkCommandPool, vkDestroyObjectHandle<VkCommandPool>>;

    // using vkCreateCommandPool =
    //     vkCreateObjectHandle<VkCommandPool>;

    // using vkDestroyCommandPool =
    //     vkDestroyObjectHandle<VkCommandPool>;

    VkCommandPool *createCommandPool()
    {
        return new VkCommandPool;
    }

    void destroyCommandPool(VkCommandPool *p)
    {
        delete p;
    }

    // template <typename T, typename deleteFuncPtr>
    // using vkUniquePtr = std::unique_ptr<T, decltype(deleteFuncPtr)>;

    // event-driven application
    // observer pattern
    namespace EDA
    {
        struct Event
        {
            virtual ~Event() = default;
        };

        class Observer
        {
        public:
            virtual ~Observer()
            {
                LOG_I("Observer::dtor");
            }
            void handleEvent(Event e)
            {
                LOG_I("Observer::handleEvent");
            }
        };
        // signal in boost / qt
        class Subject
        {
        public:
            void notify(Event e)
            {
                if (_o)
                    _o->handleEvent(e);
            }

            void attach(const std::shared_ptr<Observer> &o)
            {
                _o = o;
            }
            //...
        private:
            // observer cannot be released until subject released
            // or explicit detach it
            std::shared_ptr<Observer> _o;
        };

        class SubjectWeakPtr
        {
        public:
            void notify(Event e)
            {
                if (auto obs = _o.lock())
                {
                    // observer is still alive
                    obs->handleEvent(e);
                }
                else
                {
                    // observer is gone
                    // do nothing
                    LOG_E("Observer is gone!");
                }
            }

            void attach(const std::shared_ptr<Observer> &o)
            {
                _o = o;
            }
            //...
        private:
            // observer cannot be released until subject released
            // or explicit detach it
            std::weak_ptr<Observer> _o;
        };
    }
}