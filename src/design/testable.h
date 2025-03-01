#pragma once
#include <vector>
#include <string>
// refactoring to avoid test protected, private member function
// ownership of data moved to a different class
namespace StreamChannelDetails
{
    struct Consumer
    {
        std::string id;
    };

    class ConsumerGroup
    {
    public:
        void updateConsumer(std::string id);

    private:
        std::vector<Consumer> _grp;
    };
};


class StreamChannel
{
public:

private:
    // extra abstraction to avoid private function
    StreamChannelDetails::ConsumerGroup _cGrp;
};
