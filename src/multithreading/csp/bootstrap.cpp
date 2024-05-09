#include <iostream>
#include <sstream>
#include <queuethreadsafe.h>
#include <thread_factory.h>
#include <publisher.h>
#include <subscriber.h>
#include <bank_service.h>
#include <ui_service.h>
#include <atm_service.h>

using namespace core::utility;
using namespace core::container;
using namespace core::eda;
using namespace core::system;

int main()
{
    auto &logger = DefaultLogger::Instance();
    logger.setLogLevel(LogLevel::DEBUG);

    // // csp messaging channel
    // // QueuePtrThreadSafe<IEvent> channel;
    // // Publisher p{channel};
    // // p.publish(1);
    // // channel.push<GenericEvent<int>>(1);

    // // atm
    // // microservices: bank, atm controller, ui
    // Subscriber atm, bank, ui;
    // auto p{atm.publisher()};
    // p.publish(1);

    // // auto v = channel.wait_and_pop();
    // // std::cout << *v;

    BankService bankSvc;
    UiService uiSvc;
    ATMControllerService atmSvc(bankSvc.publisher(), uiSvc.publisher());
    auto atmPublisherChannel{atmSvc.publisher()};

    auto thread1 = CreateThread(&BankService::run, &bankSvc);
    auto thread2 = CreateThread(&UiService::run, &uiSvc);
    auto thread3 = CreateThread(&ATMControllerService::run, &atmSvc);

    bool done{false};
    while (!done)
    {
        char c = getchar();
        switch (c)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            atmPublisherChannel.publish(DigitPressedPayload(c));
            break;
        case 'b':
            atmPublisherChannel.publish(BalancedPressedPayload());
            break;
        case 'w':
            atmPublisherChannel.publish(WithdrawPressedPayload(20));
            break;
        case 'c':
            // cancel + state = decide cancel withdraw or cancel ..
            atmPublisherChannel.publish(CancelPressedPayload());
            break;
        case 'q':
            done = true;
            break;
        case 'i':
            atmPublisherChannel.publish(CardInsertedPayload("chase6550"));
            break;
        }
    }
    bankSvc.done();
    uiSvc.done();
    atmSvc.done();

    thread1->join();
    thread2->join();
    thread3->join();

    return 0;
}