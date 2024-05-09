#pragma once

#include <state_machine.h>
#include <subscriber.h>
#include <publisher.h>
#include <dispatcher.h>

using namespace core::eda;

class UiService : public IStateMachine, public CommunicationChannelExposable
{
public:
    UiService()
    {
    }

    void run() override
    {
        try
        {
            // simulation loop
            while (true)
            {
                _eventSubscriber.dispatcher()
                    .handle<DisplayEnterPinPayload>(
                        [&](const DisplayEnterPinPayload &event)
                        {
                            std::lock_guard<std::mutex> lk(_mux);
                            std::cout << "Please enter your PIN (0-9)\n";
                        })
                    .handle<DisplayPinIncorrectPayload>(
                        [&](const DisplayPinIncorrectPayload &event)
                        {
                            std::lock_guard<std::mutex> lk(_mux);
                            std::cout << "PIN incorrect\n";
                        })
                    .handle<DisplayEnterCardPayload>(
                        [&](const DisplayEnterCardPayload &event)
                        {
                            std::lock_guard<std::mutex> lk(_mux);
                            std::cout << "Please enter your card\n";
                        })
                    .handle<DisplayWithdrawOptionalsPayload>(
                        [&](const DisplayWithdrawOptionalsPayload &event)
                        {
                            std::lock_guard<std::mutex> lk(_mux);
                            std::cout << "Withdraw 20? (w)\n";
                            std::cout << "Display Balance? (b)\n";
                            std::cout << "Cancel? (c)\n";
                        })
                    .handle<DisplayWithdrawInsufficientFundsPayload>(
                        [&](const DisplayWithdrawInsufficientFundsPayload &event)
                        {
                            std::lock_guard<std::mutex> lk(_mux);
                            std::cout << "Insufficient funds\n";
                        })
                    .handle<DisplayWithdrawCancelledPayload>(
                        [&](const DisplayWithdrawCancelledPayload &event)
                        {
                            std::lock_guard<std::mutex> lk(_mux);
                            std::cout << "Withdrawal cancelled\n";
                        })
                    .handle<DisplayBalancePayload>(
                        [&](const DisplayBalancePayload &event)
                        {
                            std::lock_guard<std::mutex> lk(_mux);
                            std::cout << "The balance of your account is: " << event.amount << std::endl;
                        })
                    .handle<IssuingMoneyPayload>(
                        [&](const IssuingMoneyPayload &event)
                        {
                            std::lock_guard<std::mutex> lk(_mux);
                            std::cout << "Issuing: " << event.amount << std::endl;
                        })
                    .handle<EjectingCardPayload>(
                        [&](const EjectingCardPayload &event)
                        {
                            std::lock_guard<std::mutex> lk(_mux);
                            std::cout << "Ejecting card\n";
                        });
            }
        }
        catch (const ShutDownQueue &)
        {
        }
    }

    void done() override
    {
        publisher().publish(ShutDownQueue());
    }

    Publisher publisher() override
    {
        return _eventSubscriber.publisher();
    }

private:
    Subscriber _eventSubscriber;

    mutex _mux;
};
