#include <Island.h>
#include <iterator>
#include <iostream>
#include <unordered_set>
#include <assert.h>

int main()
{
    constexpr int R = 4, C = 4;

    Island island(R, C);
    island.addCell(1, 0);
    island.addCell(0, 1);
    island.addCell(0, 0);

    Island island2(R, C);
    island2.addCell(3, 2);
    island2.addCell(2, 3);
    island2.addCell(2, 2);

    // operator<< for cell
    // std::copy(std::begin(island.cells), std::end(island.cells), std::ostream_iterator<Cell>(std::cout, ", "));
    // std::cout << std::endl;
    // std::copy(std::begin(island2.cells), std::end(island2.cells), std::ostream_iterator<Cell>(std::cout, ", "));

    std::cout << island.hashKey() << std::endl;
    std::cout << island2.hashKey() << std::endl;

    // // based on tempalte specialization
    // {
    //     std::unordered_set<Island> islandSet;
    //     {
    //         const auto &[itr, inserted] = islandSet.insert(island);
    //         assert(islandSet.size() == 1);
    //     }
    //     {
    //         // assert(islandSet.find(island2) != islandSet.end());
    //         const auto &[itr, inserted] = islandSet.insert(island2);
    //         assert(islandSet.size() == 2);
    //     }
    // }

    // based on functor: simpler
    {
        std::unordered_set<Island, IslandHash> islandSet;
        {
            const auto &[itr, inserted] = islandSet.insert(island);
            assert(islandSet.size() == 1);
        }
        {
            // assert(islandSet.find(island2) != islandSet.end());
            const auto &[itr, inserted] = islandSet.insert(island2);
            assert(islandSet.size() == 1);
        }
    }

    return 0;
}