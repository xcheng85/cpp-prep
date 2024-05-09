#pragma once

#include <state_machine.h>
#include <subscriber.h>
#include <publisher.h>
#include <dispatcher.h>
#include <domain_event.h>

using namespace core::eda;

class BankService : public IStateMachine, public CommunicationChannelExposable
{
public:
    BankService()
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
                    .handle<VerifyPinPayload>(
                        [&](const VerifyPinPayload &event)
                        {
                            if (event.pin == "1234")
                            {
                                event.publisher.publish(PinCorrectPayload());
                            }
                            else
                            {
                                event.publisher.publish(PinCorrectPayload());
                            }
                        })
                    .handle<WithdrawPayload>(
                        [&](const WithdrawPayload &event)
                        {
                            if (_balance >= event.amount)
                            {
                                event.publisher.publish(WithdrawOkPayload());
                                _balance -= event.amount;
                            }
                            else
                            {
                                event.publisher.publish(WithdrawDeniedPayload());
                            }
                        })
                    .handle<WithdrawCompletedPayload>(
                        [&](const WithdrawCompletedPayload &event) {
                        })
                    .handle<CancelWithdrawPayload>(
                        [&](const CancelWithdrawPayload &event) {
                        })
                    .handle<QueryBlancePayload>(
                        [&](const QueryBlancePayload &event)
                        {
                            event.publisher.publish(QueryBlanceOKPayload(_balance));
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
    unsigned int _balance{100};
};
