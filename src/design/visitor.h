#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <variant>

// operation extensible on Transaction
namespace banking
{
    class Withdraw;
    class Deposit;
    class Transfer;
    // base class for all extensible ops
    class TransactionVisitor
    {
    public:
        virtual ~TransactionVisitor() = default;
        // const due to visitor can only read state, not mutate
        // this shows visitor is good for type extension
        virtual void visit(const Withdraw &) const = 0;
        virtual void visit(const Deposit &) const = 0;
        virtual void visit(const Transfer &) const = 0;
    };

    class Transaction
    {
    public:
        Transaction() = default;
        virtual ~Transaction() = default;
        // no shared_ptr needed due to no cache pointer
        // const is need for rvalue
        // tran->accept(FilterTransactionByAccountId(accountId));
        virtual void accept(const TransactionVisitor &v) = 0;
    };

    // like command
    class Withdraw : public Transaction
    {
    public:
        Withdraw(std::string accountId, double amount)
            : _accountId{accountId}, _amount{amount}
        {
        }
        // when operation happen
        virtual void accept(const TransactionVisitor &v) override
        {
            v.visit(*this);
        }

        inline auto accountId() const
        {
            return _accountId;
        }

    private:
        std::string _accountId;
        double _amount;
    };

    class Deposit : public Transaction
    {
    public:
        Deposit(std::string accountId, double amount)
            : _accountId{accountId}, _amount{amount}
        {
        }
        // when operation happen
        virtual void accept(const TransactionVisitor &v) override
        {
            v.visit(*this);
        }
        inline auto accountId() const
        {
            return _accountId;
        }

    private:
        std::string _accountId;
        double _amount;
    };

    class Transfer : public Transaction
    {
    public:
        Transfer(
            std::string srcAccountId,
            std::string dstAccountId,
            double amount)
            : _srcAccountId{srcAccountId}, _dstAccountId{dstAccountId}, _amount{amount}
        {
        }

        virtual void accept(const TransactionVisitor &v) override
        {
            v.visit(*this);
        }

        inline auto srcAccountId() const
        {
            return _srcAccountId;
        }

        inline auto dstAccountId() const
        {
            return _dstAccountId;
        }

    private:
        std::string _srcAccountId;
        std::string _dstAccountId;
        double _amount;
    };

    namespace classic
    {
        class FilterTransactionByAccountId : public TransactionVisitor
        {
        public:
            FilterTransactionByAccountId(std::string accountId)
                : _accountId{accountId}
            {
            }

            virtual void visit(const Withdraw &withdraw) const override
            {
                if (withdraw.accountId() == _accountId)
                {
                    std::cout << "filter got one for withdraw !" << std::endl;
                }
            }

            virtual void visit(const Deposit &deposit) const override
            {
                if (deposit.accountId() == _accountId)
                {
                    std::cout << "filter got one for deposit!" << std::endl;
                }
            }

            virtual void visit(const Transfer &transfer) const override
            {
                if (transfer.srcAccountId() == _accountId || transfer.dstAccountId() == _accountId)
                {
                    std::cout << "filter got one for transfer!" << std::endl;
                }
            }

        private:
            std::string _accountId;
        };

        void filterAllTransactionsByAccountId(
            const std::vector<std::unique_ptr<Transaction>> &transactions,
            std::string accountId)
        {
            for (const auto &tran : transactions)
            {
                tran->accept(FilterTransactionByAccountId(accountId));
            }
        }
    };

    namespace modern
    {
        // functor
        struct FilterTransactionByAccountId
        {
            FilterTransactionByAccountId(std::string accountId)
                : _accountId{accountId}
            {
            }

            void operator()(const Withdraw &withdraw) const
            {
                if (withdraw.accountId() == _accountId)
                {
                    std::cout << "filter got one for Withdraw!" << std::endl;
                }
            }
            void operator()(const Deposit &deposit) const
            {
                if (deposit.accountId() == _accountId)
                {
                    std::cout << "filter got one for Deposit!" << std::endl;
                }
            }
            void operator()(const Transfer &transfer) const
            {
                if (transfer.srcAccountId() == _accountId ||
                    transfer.dstAccountId() == _accountId)
                {
                    std::cout << "filter got one for Transfer!" << std::endl;
                }
            }

            std::string _accountId;
        };

        void filterAllTransactionsByAccountId(
            const std::vector<std::variant<Withdraw, Deposit, Transfer>> &transactions,
            std::string accountId)
        {
            for (const auto &tran : transactions)
            {
                // action applied to every node
                std::visit(FilterTransactionByAccountId(accountId), tran);
            }
        }
    };
};
