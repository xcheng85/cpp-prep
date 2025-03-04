#pragma once

#include <memory>
#include <unordered_set>
#include <string>
#include <functional>
#include <chrono>
#include <common.h>

namespace Observer
{
    namespace Stable
    {
        // have to be able access the subject and what field has been changed
        template <typename T>
        class Subject;

        template <typename T>
        class IObserver
        {
        public:
            IObserver() = delete;
            IObserver(std::string uuid)
                : _uuid{uuid}
            {
            }

            ~IObserver() = default;
            // different observer handle different logic
            virtual void handle(const Subject<T> &) = 0;

            inline auto uuid() const
            {
                return _uuid;
            }


        private:
            std::string _uuid;
        };

        template <typename T>
        class Subject
        {
        public:
            Subject() = delete;
            Subject(const T &) = delete;
            Subject(T &&t)
                : _state{std::move(t)}
            {
            }
            Subject(const Subject &) = delete;
            Subject &operator=(const Subject &) = delete;
            Subject(Subject &&) noexcept = default;
            Subject &operator=(Subject &&) noexcept = delete;
            void attach(std::shared_ptr<IObserver<T>> o)
            {
                _observers2.insert(o);
                LOG_I(o.use_count());
            }

            void detach(std::shared_ptr<IObserver<T>> o)
            {
                _observers2.erase(o);
            }

            void notify()
            {
                for (const auto &o : _observers2)
                {
                    o->handle(*this);
                }
            }

            const T &getState() const
            {
                return _state;
            }

        private:
            T _state;
            // raw pointer does not require custom hash
            // std::unordered_set<IObserver<T> *> _observers;
            std::unordered_set<std::shared_ptr<IObserver<T>>> _observers2;
        };
    }

    namespace Unstable
    {
        struct Player
        {
            std::string first;
            std::string last;
            unsigned int number;
        };

        class PlayerObserver : public Stable::IObserver<Player>
        {
        public:
            PlayerObserver(std::string uuid)
                : Stable::IObserver<Player>(uuid)
            {
            }
            virtual void handle(const Stable::Subject<Player> &) {

            };
        };
    }

}

// template <typename T>
// class std::hash<Observer::Stable::IObserver<T>>
// {
// public:
//     size_t operator()(Observer::Stable::IObserver<T> v) const
//     {
//         return std::hash<T *>()(v.uuid());
//     }
// };
