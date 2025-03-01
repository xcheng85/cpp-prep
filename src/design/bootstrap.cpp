#include <iostream>
#include <openclose.h>
#include <visitor.h>

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
    filterAllTransactionsByAccountId(transactions, "1000");
    return 0;
}