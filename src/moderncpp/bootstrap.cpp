#include <string>

#include <basictypes.h>
#include <enums.h>
#include <functions.h>
#include <memory.h>
#include <strings.h>
#include <memory>
#include <smartpointer.h>
#include <templatemeta.h>

using namespace std::string_literals;
using namespace std::chrono_literals;

int main()
{
    // // basic types properties
    // SyncExec("BasicTypes::testBasicTypes"s, BasicTypes::testBasicTypes);
    // // numeric limits for basic types
    // SyncExec("BasicTypes::testBasicTypeLimits", BasicTypes::testBasicTypeLimits);
    // // old style enum
    // SyncExec("Enums::testEnumOld", Enums::testEnumOld);
    // // modern enum
    // SyncExec("Functions::testFunctionVaringParameters", Functions::testFunctionVaringParameters, std::initializer_list{1, 2, 3, 4});
    // // auto and decltype(auto) for lvalue/rvalue with const
    // // cannot compile, 7 is rvalue
    // // Functions::testNonConstRvalueReference(7);
    // auto i{7};
    // // lvalue is good
    // SyncExec("Functions::testNonConstRvalueReference<int>", Functions::testNonConstRvalueReference<int>, i);
    // SyncExec("Memory::testAutoCastawayConstRef", Memory::testAutoCastawayConstRef);
    // SyncExec("Memory::testAutoNotCastawayConstRef", Memory::testAutoNotCastawayConstRef);

    // // c-string
    // SyncExec("Strings::testCString", Strings::testCString);
    // // class template argument decuction for c and std string
    // SyncExec("Strings::testClassTemplateArgumentDeduction", Strings::testClassTemplateArgumentDeduction);
    // // rvalue + non-const reference
    // // cannot compile
    // // SyncExec("Strings::testBeforeStringViewRvalue", Strings::testBeforeStringViewRvalue, "Giannis"s);
    // // string_view overccome the rvalue issue
    // SyncExec("Strings::testAfterStringView"s, Strings::testAfterStringView, "Giannis"s);

    // {
    //     //auto giannieSP = std::make_unique<std::string>("Giannis");
    //     AsyncExec("Strings::testAfterStringView"s, Strings::testStringViewDanglingPtr, "Giannis"s);
    //     //giannieSP.release();
    // }

    // smart pointer
    {
        std::unique_ptr<SmartPointers::VkCommandPool, decltype(&SmartPointers::destroyCommandPool)> cp(
            SmartPointers::createCommandPool(),
            SmartPointers::destroyCommandPool);
    }

    {
        auto cpRaw = SmartPointers::createCommandPool();
        std::shared_ptr<SmartPointers::VkCommandPool> cp(
            cpRaw,
            SmartPointers::destroyCommandPool);
        std::shared_ptr<SmartPointers::VkCommandPool> cp2(
            cp->shared_from_this());
        LOG_I(cp2.use_count());
        cp.reset();
        LOG_I(cp2.use_count());
        cp2.reset();
        LOG_I(cp2.use_count());
        // // double delete (core dumped)
        // std::shared_ptr<SmartPointers::VkCommandPool> cp2(
        //     cpRaw,
        //     SmartPointers::destroyCommandPool);

        //
    }

    // weaker ptr use case
    {
        auto obs = std::make_shared<SmartPointers::EDA::Observer>();
        auto sub = std::make_unique<SmartPointers::EDA::SubjectWeakPtr>();
        sub->attach(obs);
        LOG_TRACE_I("shared ptr counter: ", obs.use_count());
        sub->notify(SmartPointers::EDA::Event());

        // release obs
        obs.reset();
        // should report missing of observers
        sub->notify(SmartPointers::EDA::Event());
    }
    SyncExec("TemplateMeta::testTemplateMeta()", TemplateMeta::testTemplateMeta);
    // std::this_thread::sleep_for(10s);
    SyncExec("TemplateMeta::testTemplateRecursiveClass()", TemplateMeta::testTemplateRecursiveClass);

    return 0;
}