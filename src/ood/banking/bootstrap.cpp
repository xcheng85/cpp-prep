#include <string>
#include <queue>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <format>
#include <mutex>
#include <thread>

// design a debit banking system with
// create account: checking and saving acct

// withdraw: from which account, limit, protection

// deposit: to which account

// transfer functionality, between two account, protection, transaction, one atomic

// Additionally the interviewer askes to get the account with largest transaction.

// ood

// Data Model:
// Account: fields
// owner: string, type: balance, withdraw limits, account num: string, routing number: string

enum ACCOUNT_TYPE : int
{
    CHECKING = 0,
    SAVING
};

enum TRANSACTION_TYPE : int
{
    WITHDRAW = 0,
    DEPOSIT,
    TRANSFER
};

// app-domain exception
struct Transaction
{
    double amount;
    TRANSACTION_TYPE type;
    // const is a must
    bool operator<=(const Transaction &other) const
    {
        return this->amount <= other.amount;
    }
    bool operator<(const Transaction &other) const
    {
        return this->amount < other.amount;
    }
};
constexpr double gDefaultWithdrawLimit = 500;
struct Account
{
    Account() = delete;
    Account(
        std::string route,
        std::string num,
        ACCOUNT_TYPE type) : routingNum{route}, num{num}, type{type}
    {
    }

    ~Account() = default;

    std::string routingNum;
    std::string num;
    ACCOUNT_TYPE type;
    double balance{0};
    double withdrawLimit{gDefaultWithdrawLimit};
    // std::vector<Transaction> transactions;
    //  default is max queue
    // std::less<Transaction>()>, no ()
    std::priority_queue<Transaction, std::vector<Transaction>,
                        std::less<Transaction>>
        maxTransactionQueue;

    std::mutex balanceMutex, pqMutex;

    // positive: deposite, negative: withdraw
    void update(double amount)
    {
        bool isWithdraw = amount < 0;
        if (isWithdraw)
        {
            if (amount < 0.01 || amount >= balance)
            {
                auto errMsg = std::format("Account: {} does not have enough balance to withdraw {} !", num, amount);
                throw std::runtime_error(errMsg);
            }
            if (amount >= withdrawLimit)
            {
                auto errMsg = std::format("{} exceeds day withdraw limit {} !", amount, withdrawLimit);
                throw std::runtime_error(errMsg);
            }
        }

        // create transaction and also deduct and add transaction
        // mutex double balance{0}; and mutex for priority queue
        std::scoped_lock lock{balanceMutex, pqMutex};
        balance += amount;
        maxTransactionQueue.push(Transaction{
            std::abs(amount),
            isWithdraw ? TRANSACTION_TYPE::WITHDRAW : TRANSACTION_TYPE::DEPOSIT});
    }
};

std::iostream &operator<<(std::iostream &of, const Transaction &t)
{
    std::cout << "Transaction Amount: " << t.amount << ", type: " << t.type << std::endl;
    return of;
}

class BankSystem
{
public:
    BankSystem() = default;
    // exception
    void createAccount(
        std::string route,
        std::string account,
        ACCOUNT_TYPE type)
    {
        if (_accounts.count(account))
        {
            auto errMsg = std::format("Account: {} already exists !", account);
            throw std::runtime_error(errMsg);
        }
        _accounts.insert(std::make_pair(account, std::make_unique<Account>(
                                                     route, account, type)));
    }

    void withdraw(std::string account, double amount)
    {
        // validate .cent
        if (!_accounts.count(account))
        {
            auto errMsg = std::format("Account: {} does not exists !", account);
            throw std::runtime_error(errMsg);
        }
        _accounts[account]->update(-amount);
    }

    void deposite(std::string account, double amount)
    {
        // validate .cent
        if (!_accounts.count(account))
        {
            auto errMsg = std::format("Account: {} does not exists !", account);
            throw std::runtime_error(errMsg);
        }
        _accounts[account]->update(amount);
    }

    void transfer(std::string fromAccount, std::string toAccount, double amount)
    {
        if (!_accounts.count(fromAccount))
        {
            auto errMsg = std::format("Account: {} does not exists !", fromAccount);
            throw std::runtime_error(errMsg);
        }
        if (!_accounts.count(toAccount))
        {
            auto errMsg = std::format("Account: {} does not exists !", toAccount);
            throw std::runtime_error(errMsg);
        }

        auto &mux1 = _accounts[fromAccount]->balanceMutex;
        auto &mux2 = _accounts[toAccount]->balanceMutex;
        auto &mux3 = _accounts[fromAccount]->pqMutex;
        auto &mux4 = _accounts[toAccount]->pqMutex;
        std::scoped_lock lock{mux1, mux2, mux3, mux4};
        if (_accounts[fromAccount]->balance < amount)
        {
            auto errMsg = std::format("Account: {} does not have enough balance to transfer!", fromAccount);
            throw std::runtime_error(errMsg);
        }
        _accounts[fromAccount]->balance -= amount;
        _accounts[toAccount]->balance += amount;
        _accounts[fromAccount]->maxTransactionQueue.push(Transaction{
            amount,
            TRANSACTION_TYPE::TRANSFER});
        _accounts[toAccount]->maxTransactionQueue.push(Transaction{
            amount,
            TRANSACTION_TYPE::TRANSFER});
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Account>> _accounts;
};

int main()
{
    try
    {
        auto banksystem = std::make_unique<BankSystem>();
        banksystem->createAccount("110614", "6550", ACCOUNT_TYPE::CHECKING);
        banksystem->createAccount("110614", "7309", ACCOUNT_TYPE::SAVING);

        banksystem->deposite("6550", 100);
        banksystem->transfer("6550", "7309", 50);

        auto dangling = new BankSystem();
    }
    catch (std::runtime_error ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}