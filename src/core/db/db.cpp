#include <db.h>

namespace core::db
{
    DBInstance &DBInstance::instance()
    {
        static DBInstance singleton{DefaultLogger::Instance()};
        return singleton;
    }

    std::unique_ptr<DBClient> DBInstance::createClient(std::string_view connectionString)
    {
        _logger.info(connectionString);
        return std::make_unique<DBClient>(connectionString);
    }

    DBInstance::DBInstance(ILogger &logger) : _logger{logger} {

                                              };
}