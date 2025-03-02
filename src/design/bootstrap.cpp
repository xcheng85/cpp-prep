#include <iostream>
#include <algorithm>
#include <openclose.h>
#include <visitor.h>
#include <strategy.h>
#include <command.h>

int main()
{
    using namespace OCP;
    auto serializer = std::make_shared<Serialization>();
    auto assimp = std::make_shared<AssimpOCP>(serializer);
    ByteStream buffer;
    assimp->serialize(buffer);

    auto assimp2 = std::make_shared<AssimpOCP>(serializer);
    testSwap(*assimp, *assimp2);

    // visitor for operation Open-close principle
    using namespace banking;
    std::vector<std::unique_ptr<Transaction>> transactions;
    transactions.emplace_back(std::make_unique<Withdraw>(
        "1000", 1000));
    transactions.emplace_back(std::make_unique<Deposit>(
        "2000", 2000));
    transactions.emplace_back(std::make_unique<Transfer>(
        "1000", "3000", 2000));
    classic::filterAllTransactionsByAccountId(transactions, "1000");

    std::vector<std::variant<Withdraw, Deposit, Transfer>> transactionVariants;
    transactionVariants.emplace_back(Withdraw(
        "1000", 1000));
    transactionVariants.emplace_back(Deposit(
        "2000", 2000));
    transactionVariants.emplace_back(Transfer(
        "1000", "3000", 2000));
    modern::filterAllTransactionsByAccountId(transactionVariants, "1000");

    // strategy
    std::vector<std::unique_ptr<Strategy::Stable::Object>> objects;
    auto boxRenderer = std::make_unique<Strategy::Unstable::VulkanBoxRenderer>();
    auto sphereRenderer = std::make_unique<Strategy::Unstable::VulkanSphereRenderer>();

    objects.emplace_back(std::make_unique<Strategy::Unstable::Box>(
        10.f, 10.f, 10.f,
        std::move(boxRenderer)));
    objects.emplace_back(std::make_unique<Strategy::Unstable::Sphere>(
        10.f,
        std::move(sphereRenderer)));
    // objects.emplace_back(std::make_unique<Strategy::Unstable::StaticPoly::Box<Strategy::Unstable::VulkanBoxRenderer>>(
    //     20.f, 20.f, 20.f,
    //     std::move(boxRenderer)));

    // objects.emplace_back(std::make_unique<Strategy::Unstable::StaticPoly::Box<Strategy::Unstable::VulkanSphereRenderer>>(
    //     20.f,
    //     std::move(sphereRenderer)));
    for (const auto &obj : objects)
    {
        obj->render();
    }

    // static strategy pattern

    // command pattern
    Command::BankerSession session;
    std::string act, bankcmd, amount;
    // // ctrl + D on linux/mac, Ctrl-Z on windows to exit loop
    // while (std::cin)
    // {
    //     std::cin >> bankcmd;
    //     transform(bankcmd.begin(), bankcmd.end(), bankcmd.begin(),
    //               ::tolower);
    //     if (bankcmd == "login")
    //     {
    //         std::cin >> act;
    //         session.login(act);
    //     }
    //     else if (bankcmd == "withdraw")
    //     {
    //         std::cin >> amount;
    //         auto cmd = std::make_unique<Command::WithdrawCommand>(std::stod(amount));
    //         session.apply(std::move(cmd));
    //     }
    //     else if (bankcmd == "deposit")
    //     {
    //         std::cin >> amount;
    //         LOG_I(std::stod(amount));
    //         auto cmd = std::make_unique<Command::DepositeCommand>(std::stod(amount));
    //         session.apply(std::move(cmd));
    //     }
    //     else if (bankcmd == "balance")
    //     {
    //         session.getCurrentBalance(act);
    //     }
    //     else if (bankcmd == "endSession")
    //     {
    //         session.endSession();
    //     }
    //     else
    //     {
    //         assert(false);
    //     }
    // }

    // thread pool + command
    Command::ThreadPool tp(2);
    std::vector<int> input{1, 1, 1};
    tp.schedule(std::make_unique<Command::Aggregation<int>>(input));
    tp.schedule(std::make_unique<Command::MaxValue<int>>(input));
    tp.wait();

    return 0;
}