#include "app.h"
#include <logger.h>

using namespace core::utility;

int main()
{
    // auto logger is wrong
    auto &logger = DefaultLogger::Instance();
    DBInstance &db = DBInstance::instance();
    App app{db, logger, 10};
    app.init();
    app.run();
}