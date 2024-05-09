#pragma once

#include <subscriber.h>
#include <publisher.h>
#include <dispatcher.h>

using namespace core::eda;

class IStateMachine
{
public:
    virtual void run() = 0;
    virtual void done() = 0;
};

// mixin class "-able" relationship
// Impl techniques
// 1. multiple-inheritance
// 2. class templates
// 3. CRTP(curiously recurring template pattern)

// api to expose publisher channel

// method1: multiple-inheritance
class CommunicationChannelExposable {
    public:
      virtual Publisher publisher() = 0;
};