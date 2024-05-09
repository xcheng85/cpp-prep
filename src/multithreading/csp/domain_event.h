#pragma once

#include <string>
#include <publisher.h>

using namespace core::eda;

class IEventPayload
{
};

// state of state machine
// publisher is the channel in golang
struct VerifyPinPayload : public IEventPayload
{
    VerifyPinPayload(const std::string &account,
                     const std::string &pin,
                     Publisher publisher)
        : account{account}, pin{pin}, publisher{publisher}
    {
    }
    // payload
    std::string account;
    std::string pin;
    mutable Publisher publisher; // publish event to a queue owned by a service
};

struct PinCorrectPayload : public IEventPayload
{
};
struct PinIncorrectPayload : public IEventPayload
{
};

struct WithdrawPayload : IEventPayload
{
    WithdrawPayload(const std::string &account,
                    const unsigned int &amount,
                    Publisher publisher)
        : account{account}, amount(amount), publisher{publisher}
    {
    }

    std::string account;
    unsigned amount;
    mutable Publisher publisher; // publish event to a queue owned by a service
};

struct WithdrawOkPayload : public IEventPayload
{
};

struct WithdrawDeniedPayload : public IEventPayload
{
};

struct WithdrawCompletedPayload : public IEventPayload
{
    WithdrawCompletedPayload(const std::string &account, const unsigned int &amount)
        : account{account}, amount(amount)
    {
    }
    std::string account;
    unsigned amount;
};

struct CancelWithdrawPayload : public IEventPayload
{
     CancelWithdrawPayload(const std::string &account, const unsigned int &amount)
        : account{account}, amount(amount)
    {
    }
    std::string account;
    unsigned amount;
};

struct QueryBlancePayload : public IEventPayload
{
    QueryBlancePayload(const std::string &account, Publisher publisher)
        : account{account}, publisher{publisher}
    {
    }
    std::string account;
    mutable Publisher publisher; // publish event to a queue owned by a service
};

struct QueryBlanceOKPayload : public IEventPayload
{
    QueryBlanceOKPayload(unsigned amount) : amount{amount}
    {
    }
    unsigned amount;
};

struct DisplayEnterPinPayload : public IEventPayload
{
};

struct DisplayPinIncorrectPayload : public IEventPayload
{
};

struct DisplayEnterCardPayload : public IEventPayload
{
};

struct DisplayWithdrawOptionalsPayload : public IEventPayload
{
};

struct DisplayWithdrawInsufficientFundsPayload : public IEventPayload
{
};

struct DisplayWithdrawCancelledPayload : public IEventPayload
{
};

struct IssuingMoneyPayload : public IEventPayload
{
    IssuingMoneyPayload(unsigned int amount) : amount{amount}
    {
    }
    unsigned int amount;
};

struct DisplayBalancePayload : public IEventPayload
{
    DisplayBalancePayload(unsigned int amount) : amount{amount}
    {
    }
    unsigned int amount;
};

struct EjectingCardPayload : public IEventPayload
{
};

//
// event from ui
struct CardInsertedPayload : public IEventPayload
{
    CardInsertedPayload() = delete;
    explicit CardInsertedPayload(const std::string &account) : account{account}
    {
    }
    std::string account;
};

// pin related
struct DigitPressedPayload : public IEventPayload
{
    DigitPressedPayload() = delete;
    explicit DigitPressedPayload(char digit) : digit{digit}
    {
    }
    std::string digit;
};

struct RevertLastDigitPressedPayload : public IEventPayload
{
};

struct CancelPressedPayload : public IEventPayload
{
};

// after pin passed, menu:
// user can do
struct WithdrawPressedPayload : public IEventPayload
{
    explicit WithdrawPressedPayload(unsigned int amount) : amount{amount}
    {
    }
    unsigned int amount;
};

struct BalancedPressedPayload : public IEventPayload
{
};