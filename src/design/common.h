#pragma once

#include <vector>
#include <iostream>
#include <source_location>
#include <format>

using ByteStream = std::vector<std::byte>;

template <typename T>

concept Streamable = requires(std::ostream os, T value) {
    { os << value };
};

#define LOG_I(T) logging(T)

template <Streamable T>
inline void logging(
    const T& message,
    const std::source_location &location = std::source_location::current())
{
    std::cout << std::format("File: {}, Line: {}, {}\n",location.file_name(),
    location.line(), message );
}