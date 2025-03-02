#pragma once

#include <string>
#include <assert.h>
#include <limits>
#include <vector>
#include <unordered_map>
#include <stack>
#include <memory>
#include <optional>
#include <common.h>

namespace Command
{
    constexpr double eps = std::numeric_limits<double>::epsilon();
    // SRP, not coupling with
    class BankingCommand
    {
    public:
        virtual ~BankingCommand() = default;
        // balance
        // like angular state mutation, stateless, return new state
        virtual double execute(double balance) const = 0;
        virtual double undo(double balance) const = 0;
    };

    class DepositeCommand : public BankingCommand
    {
    public:
        DepositeCommand() = delete;
        explicit DepositeCommand(double amount)
            : _amount{amount}
        {
        }

        virtual double execute(double balance) const override
        {
            LOG_I(_amount);
            return balance + _amount;
        }

        virtual double undo(double balance) const override
        {
            return balance - _amount;
        }

    private:
        double _amount{0.0};
    };

    class WithdrawCommand : public BankingCommand
    {
    public:
        WithdrawCommand() = delete;
        explicit WithdrawCommand(double amount)
        :_amount{amount}
        {

        }

        virtual double execute(double balance) const override
        {
            return balance - _amount;
        }

        virtual double undo(double balance) const override
        {
            return balance + _amount;
        }

    private:
        double _amount{0.0};
    };

    // mimic after login
    class BankerSession
    {
    public:
        void login(std::string act) {
            _act = act;
        }

        void apply(std::unique_ptr<BankingCommand> command)
        {
            assert(_act.has_value());
            auto act = _act.value();
            // check act exceptions, todo
            // ngrx state mutation
            _balances = command->execute(_balances);
            LOG_I(_balances);
            // ownership transfer
            _cmdHistory.push(std::move(command));
        }

        void undo(std::string act)
        {
            assert(_act.has_value());
            if (_cmdHistory.empty())
                return;
            auto lastCmd = std::move(_cmdHistory.top());
            _cmdHistory.pop();
            _balances = lastCmd->undo(_balances);
        }

        auto getCurrentBalance(std::string act)
        {
            assert(_act.has_value());
            LOG_I(_balances);
            return _balances;
        }

        void endSession()
        {
            // swap idiom
            _act.reset();
            std::stack<std::unique_ptr<BankingCommand>>{}
                .swap(_cmdHistory);
        }

    private:
        std::optional<std::string> _act{std::nullopt};
        // each account has balance and history of command
        // cache access pattern frequency different, keep in two ds.
        // unintialized double is dangerous
        double _balances{0.0};
        std::stack<std::unique_ptr<BankingCommand>> _cmdHistory;
    };
}