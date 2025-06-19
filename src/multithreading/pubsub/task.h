#pragma once

#include <iostream>

// pointer will be passed around, shared_ptr ?
class ITask
{
public:
    virtual void exec() = 0;
    virtual ~ITask()
    {
        std::cout << "ITask::~ITask()" << std::endl;
    }
};

class CreateSessionTask : public ITask
{
public:
    virtual void exec() override
    {
        std::cout << "CreateSessionTask::exec()" << std::endl;
    }
};