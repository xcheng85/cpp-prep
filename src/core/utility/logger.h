#pragma once

#include <iostream>
#include <format>

using namespace std;

namespace core::utility
{
    class ILogger
    {
    public:
        virtual ~ILogger() {}
        virtual void info(string_view) = 0;
        virtual void warn(string_view) = 0;
        virtual void error(string_view) = 0;
        virtual void debug(string_view) = 0;
    };

    class DefaultLogger : private ILogger
    {
    public:
        enum LogLevel : int
        {
            DEBUG,
            INFO,
            WARN,
            ERROR
        };

        static ILogger& Instance();

        inline void info(string_view s) override
        {
            if (_logLevel <= INFO)
            {
                cout << format("[INFO]: {}", s) << "\n";
            }
        }

        inline void warn(string_view s)
        {
            if (_logLevel <= WARN)
            {
                cout << format("[WARN]: {}", s) << "\n";
            }
        }

        inline void error(string_view s)
        {
            if (_logLevel <= ERROR)
            {
                cerr << format("[ERROR]: {}", s) << "\n";
            }
        }

        inline void debug(string_view s)
        {
            if (_logLevel <= DEBUG)
            {
                cout << format("[DEBUG]: {}", s) << "\n";
            }
        }

    private:
        DefaultLogger();
        DefaultLogger(const DefaultLogger &) = delete;
        DefaultLogger &operator=(const DefaultLogger &) = delete;
        DefaultLogger(DefaultLogger &&) = delete;
        DefaultLogger &operator=(DefaultLogger &&) = delete;

        static constexpr LogLevel sDefaultLogLevel{LogLevel::INFO};
        LogLevel _logLevel{DefaultLogger::sDefaultLogLevel};
    };
}