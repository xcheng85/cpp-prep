#include <iostream>
#include <openclose.h>
#include <visitor.h>
#include <strategy.h>

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

    for(const auto& obj : objects) {
        obj->render();
    }

    return 0;
}