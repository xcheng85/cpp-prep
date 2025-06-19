#include <consumer.h>
#include <stream.h>
#include <chrono>

void Consumer::start() {
      while (_running)
        {
            if (_ready)
            {
                _ready = false;
                _task->exec();
            }
            // add himself back to the streamer idle queue
            bool idle = _stream->addConsumer(getptr());
            if(idle) {
                // In computing, a spurious wakeup occurs when a thread wakes up 
                //from waiting on a condition variable and finds that the condition is still unsatisfied. 
                //It is referred to as spurious because the thread has seemingly been awoken for no reason. 
                bool satisfiedCondition = (_ready && _running);
                while(!satisfiedCondition) {
                    // spur
                    // timeout 1s
                    if(_cv.wait_for(_ulock, std::chrono::seconds(1))==std::cv_status::timeout){

                    }
                    satisfiedCondition = (_ready && _running);
                }
            }
        }
}