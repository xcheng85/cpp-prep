#include <string>

#include <basictypes.h>
#include <enums.h>
#include <functions.h>
#include <memory.h>
#include <strings.h>

using namespace std::string_literals;

int main()
{
    // basic types properties
    SyncExec("BasicTypes::testBasicTypes"s, BasicTypes::testBasicTypes);
    // numeric limits for basic types
    SyncExec("BasicTypes::testBasicTypeLimits", BasicTypes::testBasicTypeLimits);
    // old style enum
    SyncExec("Enums::testEnumOld", Enums::testEnumOld);
    // modern enum
    SyncExec("Functions::testFunctionVaringParameters", Functions::testFunctionVaringParameters, std::initializer_list{1, 2, 3, 4});
    // auto and decltype(auto) for lvalue/rvalue with const
    // cannot compile, 7 is rvalue
    // Functions::testNonConstRvalueReference(7);
    auto i{7};
    // lvalue is good
    SyncExec("Functions::testNonConstRvalueReference<int>", Functions::testNonConstRvalueReference<int>, i);
    SyncExec("Memory::testAutoCastawayConstRef", Memory::testAutoCastawayConstRef);
    SyncExec("Memory::testAutoNotCastawayConstRef", Memory::testAutoNotCastawayConstRef);
    
    // c-string
    SyncExec("Strings::testCString", Strings::testCString);
    SyncExec("Strings::testClassTemplateArgumentDeduction", Strings::testClassTemplateArgumentDeduction);
    return 0;
}