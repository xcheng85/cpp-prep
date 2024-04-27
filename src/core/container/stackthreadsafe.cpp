#include <stackthreadsafe.h>

namespace core::container
{
    const char *EmptyStack::what() const noexcept
    {
        return "Stack is empty";
    }
}