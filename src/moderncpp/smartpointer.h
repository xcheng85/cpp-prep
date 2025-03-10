#pragma once

#include <memory>
#include <shared.h>

namespace SmartPointers
{
    // interface for smart point (both unique_ptr and shared_ptr)
    // Dereferencing (operator *)
    // Indirection (operator ->)

    // unique_ptr: not copyable

    template <typename T>
    class CustomUniquePtr
    {
    public:
        // 2nd ctor of unique_ptr besides make_unique
        CustomUniquePtr() = delete;
        explicit CustomUniquePtr(T *rawPtr)
            : _ptr{rawPtr}
        {
            LOG_I("CustomUniquePtr::ctor");
        }
        CustomUniquePtr(const CustomUniquePtr &other) = delete;
        CustomUniquePtr &operator=(const CustomUniquePtr &other) = delete;
        CustomUniquePtr(CustomUniquePtr &&other) noexcept
        {
            LOG_I("CustomUniquePtr::rvalue copy ctor");
            _ptr = std::move(other._ptr);
        }
        CustomUniquePtr &operator=(CustomUniquePtr &&other) noexcept
        {
            LOG_I("CustomUniquePtr::rvalue =");
            _ptr = std::move(other._ptr);
            return *this;
        }

        ~CustomUniquePtr()
        {
            LOG_I("CustomUniquePtr::dtor");
            delete _ptr;
        }

        T &operator*()
        {
            return *_ptr;
        }

        T *operator->()
        {
            return _ptr;
        }

    private:
        T *_ptr;
    };

    // Single Responsibility
    class RefCounter
    {

    public:
        void AddRef()
        {
            _count++;
        }

        int Release()
        {
            LOG_I("RefCounter::Release");
            return --_count;
        }

        inline auto Count() const
        {
            return _count;
        }

    private:
        int _count{0};
    };

    template <typename T>
    class CustomSharedPtr
    {
    public:
        CustomSharedPtr()
        {
            _refCounter = new RefCounter();
            _refCounter->AddRef();
        }

        CustomSharedPtr(T *ptr)
            : _ptr(ptr)
        {
            _refCounter = new RefCounter();
            _refCounter->AddRef();
        }

        // key: shared_ptr is copyable
        // copy of pointer and copy of data
        CustomSharedPtr(const CustomSharedPtr &other)
            : _ptr(other._ptr), _refCounter(other._refCounter)
        {
            _refCounter->AddRef();
        }
        // most critical, old memory could be released.
        CustomSharedPtr &operator=(const CustomSharedPtr &other)
        {
            if (this != &other)
            {
                if (_refCounter->Release() == 0)
                {
                    delete _ptr;
                    delete _refCounter;
                }

                _ptr = other._ptr;
                _refCounter = other._refCounter;
                // increase counter
                _refCounter->AddRef();
            }
            return *this;
        }

        ~CustomSharedPtr()
        {
            if (_refCounter->Release() == 0)
            {
                delete _ptr;
                delete _refCounter;
            }
        }

        T &operator*()
        {
            return *_ptr;
        }

        T *operator->()
        {
            return _ptr;
        }

        size_t use_count() const
        {
            return _refCounter->Count();
        }

    private:
        T *_ptr{nullptr};
        // composition as strategy pattern.
        RefCounter *_refCounter{nullptr};
    };

    void testCustomUniquePtr()
    {
        CustomUniquePtr<int> p(new int);
    }

    void testCustomSharedPtr()
    {
        CustomSharedPtr<int> p(new int);
        CustomSharedPtr<int> p2(p);
        CustomSharedPtr<int> p3 = (p2);
        LOG_I(p.use_count());
    }

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