#pragma once

#include <functional>
#include <state_machine.h>
#include <subscriber.h>
#include <publisher.h>
#include <dispatcher.h>
#include <domain_event.h>

using namespace core::eda;

// ATM controller access to upstream messaging channels
class ATMControllerService : public IStateMachine, public CommunicationChannelExposable
{
public:
    ATMControllerService(
        Publisher bankServiceChannel,
        Publisher uiServiceChannel)
        : _bankServiceChannel{bankServiceChannel},
          _uiServiceChannel{uiServiceChannel}
    {
    }

    void run() override
    {
        try
        {
            _state = &ATMControllerService::waitForCardState;
            // simulation loop
            while (true)
            {
                // how to call std::function which is pointing to instance method
                _state(*this);
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
    // state: Wait for card
    void waitForCardState()
    {
        _uiServiceChannel.publish(DisplayEnterCardPayload());
        // the state mutation arrow
        _eventSubscriber.dispatcher()
            .handle<CardInsertedPayload>(
                [&](const CardInsertedPayload &payload)
                {
                    // reset session session
                    _account = payload.account;
                    _pin = "";
                    _withdrawAmount = 0;

                    _uiServiceChannel.publish(DisplayEnterPinPayload());
                    // state mutation
                    _state = &ATMControllerService::getPinState;
                });
    }

    void getPinState()
    {
        _eventSubscriber.dispatcher()
            .handle<DigitPressedPayload>(
                [&](const DigitPressedPayload &payload)
                {
                    constexpr uint8_t pinLength = 4;
                    _pin += payload.digit;

                    cout << _pin << "\n";

                    // automically connect to the bank service
                    // diff: size() vs length()
                    if (_pin.length() == pinLength)
                    {
                        // share the atm service channel to the bankService, so the bank could send message back using it
                        // this pattern provide the bi-directional communication
                        _bankServiceChannel.publish(VerifyPinPayload(_account, _pin, _eventSubscriber.publisher()));
                        _state = &ATMControllerService::verifyingPinState;
                    }
                })
            .handle<RevertLastDigitPressedPayload>(
                [&](const RevertLastDigitPressedPayload &payload)
                {
                    if (!_pin.empty())
                    {
                        _pin.pop_back();
                    }
                })
            .handle<CancelPressedPayload>(
                [&](const CancelPressedPayload &payload)
                {
                    _state = &ATMControllerService::ejectingCardState;
                });
    }

    // why verifying not verified ?
    // block call in handle
    void verifyingPinState()
    {
        // timing of the cancel button pressed.
        // a block call until bank service send back PinCorrectPayload/PinIncorrect, etc
        _eventSubscriber.dispatcher()
            .handle<PinCorrectPayload>(
                [&](const PinCorrectPayload &payload)
                {
                    _state = &ATMControllerService::waitForUserActionState;
                })
            .handle<PinIncorrectPayload>(
                [&](const PinIncorrectPayload &payload)
                {
                    _uiServiceChannel.publish(DisplayPinIncorrectPayload());
                    _state = &ATMControllerService::ejectingCardState;
                })
            .handle<CancelPressedPayload>(
                [&](const CancelPressedPayload &msg)
                {
                    _state = &ATMControllerService::ejectingCardState;
                });
    }

    void ejectingCardState()
    {
        _uiServiceChannel.publish(EjectingCardPayload());
        // start all over again
        _state = &ATMControllerService::waitForCardState;
    }

    // menu state
    void waitForUserActionState()
    {
        _uiServiceChannel.publish(DisplayWithdrawOptionalsPayload());
        _eventSubscriber.dispatcher()
            .handle<WithdrawPressedPayload>(
                [&](const WithdrawPressedPayload &payload)
                {
                    _withdrawAmount = payload.amount;
                    // bank service will send back the result through shared channel
                    _bankServiceChannel.publish(WithdrawPayload(_account, payload.amount, _eventSubscriber.publisher()));
                    _state = &ATMControllerService::processingWithdrawState;
                })
            .handle<BalancedPressedPayload>(
                [&](const BalancedPressedPayload &payload)
                {
                    _bankServiceChannel.publish(QueryBlancePayload(_account, _eventSubscriber.publisher()));
                    _state = &ATMControllerService::processingBalanceQueryState;
                })
            .handle<CancelPressedPayload>(
                [&](const CancelPressedPayload &payload)
                {
                    _state = &ATMControllerService::ejectingCardState;
                });
    }

    void processingWithdrawState()
    {
        _eventSubscriber.dispatcher()
            .handle<WithdrawOkPayload>(
                [&](const WithdrawOkPayload &payload)
                {
                    _uiServiceChannel.publish(IssuingMoneyPayload(_withdrawAmount));
                    _bankServiceChannel.publish(WithdrawCompletedPayload(_account, _withdrawAmount));
                    _state = &ATMControllerService::ejectingCardState;
                })
            .handle<WithdrawDeniedPayload>(
                [&](const WithdrawDeniedPayload &payload)
                {
                    _uiServiceChannel.publish(DisplayWithdrawInsufficientFundsPayload());
                    _state = &ATMControllerService::ejectingCardState;
                })
            .handle<CancelPressedPayload>(
                [&](const CancelPressedPayload &payload)
                {
                    _bankServiceChannel.publish(CancelWithdrawPayload(_account, _withdrawAmount));
                    _uiServiceChannel.publish(DisplayWithdrawCancelledPayload());
                    _state = &ATMControllerService::ejectingCardState;
                });
    }

    void processingBalanceQueryState()
    {
        _eventSubscriber.dispatcher()
            .handle<QueryBlanceOKPayload>(
                [&](const QueryBlanceOKPayload &payload)
                {
                    _uiServiceChannel.publish(DisplayBalancePayload(payload.amount));
                    // state mutated back
                    _state = &ATMControllerService::waitForUserActionState;
                })
            .handle<CancelPressedPayload>(
                [&](const CancelPressedPayload &payload)
                {
                    _state = &ATMControllerService::ejectingCardState;
                });
    }

    Subscriber _eventSubscriber;
    Publisher _bankServiceChannel;
    Publisher _uiServiceChannel;

    // state of an atm session
    std::string _account;
    unsigned int _withdrawAmount;
    std::string _pin;

    // https://en.cppreference.com/w/cpp/utility/functional/function
    std::function<void(ATMControllerService &)> _state;
};
