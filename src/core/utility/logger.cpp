#include <logger.h>

namespace core::utility
{
    // thread-safe after c++11
    ILogger &DefaultLogger::Instance()
    {
        static DefaultLogger instance;
        return instance;
    }
    
    DefaultLogger::DefaultLogger(){

    };
}