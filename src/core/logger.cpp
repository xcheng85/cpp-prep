#include <logger.h>

namespace core::utility
{
    ILogger &DefaultLogger::Instance()
    {
        static DefaultLogger instance;
        return instance;
    }
    
    DefaultLogger::DefaultLogger(){

    };
}