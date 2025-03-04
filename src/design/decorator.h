#pragma once

#include <string>
#include <memory>

namespace Decorator
{
    // chain of different decorator layers
    // nba2k player score
    class IObject
    {
    public:
        virtual ~IObject() = default;
        virtual int score() const = 0;
    };

    class Player : public IObject
    {
    public:
        Player(std::string name, int score)
            : _score{score}, _name{std::move(name)}
        {
        }

        inline const std::string &name() const
        {
            return _name;
        }

        inline int score() const
        {
            return _score;
        }

    private:
        std::string _name{};
        int _score{0};
    };

    class Coach : public IObject
    {
    public:
        Coach(std::string name, int score)
            : _score{score}, _name{std::move(name)}
        {
        }

        inline const std::string &name() const
        {
            return _name;
        }

        inline int score() const
        {
            return _score;
        }

    private:
        std::string _name{};
        int _score{0};
    };

    // ownership of Object transferable
    class IDecorated : public IObject
    {
    public:
        IDecorated() = delete;
        IDecorated(std::unique_ptr<IObject> obj)
            : _obj{std::move(obj)}
        {
        }

    protected:
        // real decorator need to access the original score
        // reference still polymophsim
        IObject &obj()
        {
            return *_obj;
        }

        const IObject &obj() const
        {
            return *_obj;
        }

    private:
        std::unique_ptr<IObject> _obj;
    };

    // real decoratr
    class Injured : public IDecorated
    {
    public:
        Injured() = delete;
        Injured(double coefficient, std::unique_ptr<IObject> obj)
            : IDecorated(std::move(obj)), _coefficient{coefficient}
        {
        }

        virtual int score() const override
        {
            return obj().score() * _coefficient;
        }

    private:
        // state of This Decorator
        double _coefficient;
    };

    class HotStreak : public IDecorated
    {
    public:
        HotStreak() = delete;
        HotStreak(double coefficient, std::unique_ptr<IObject> obj)
            : IDecorated(std::move(obj)), _coefficient{coefficient}
        {
        }

        virtual int score() const override
        {
            return obj().score() * _coefficient;
        }

    private:
        // state of This Decorator
        double _coefficient;
    };
}