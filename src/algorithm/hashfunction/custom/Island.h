#pragma once
#include <set>
#include <functional>
#include <iostream>
#include <format>

// exception of putting stuff to namespace std:
// hash is std class tempalte, his specialization allow this.
struct Cell
{
    int i, j, numRows, numCols;
    Cell() = delete;
    // required for unorded_set
    bool operator==(const Cell &otherPoint) const = default;
    explicit Cell(int numRows, int numCols, int i, int j)
        : i{i}, j{j}, numRows{numRows}, numCols{numCols}
    {
    }

    int offset1d() const
    {
        return i * numCols + j;
    }
};

std::ostream &operator<<(std::ostream &os, const Cell &c)
{
    os << std::format("[{}, {}]", c.i, c.j);
    return os;
}

bool operator<(const Cell &c1, const Cell &c2)
{
    return c1.i < c2.i || ((c1.i == c2.i) && (c1.j < c2.j));
}

struct Island
{
    int numRows, numCols;
    // rely on operator<
    std::set<Cell> cells;

    Island() = delete;
    Island(int numRows, int numCols)
        : numRows{numRows}, numCols{numCols}
    {
    }
    // all the basic types
    // required for unorded_set
    // must compare hashKey.
    bool operator==(const Island &otherPoint) const
    {
        return hashKey() == otherPoint.hashKey();
    }

    void addCell(int i, int j)
    {
        cells.emplace(numRows, numCols, i, j);
    }

    // mapping to a unique index
    inline int hashKey() const
    {
        int dt{0};
        for (auto itr{++cells.begin()}; itr != cells.end(); ++itr)
        {
            dt += itr->offset1d() - cells.begin()->offset1d();
        }
        return dt;
    }
};

// functor
struct IslandHash
{
    auto operator()(const Island &i) const
    {
        return std::hash<int>{}(i.hashKey());
    }
};

// // hash template specialization
// namespace std
// {
//     template <>
//     struct hash<Island>
//     {
//         auto operator()(const Island &i) const
//         {
//             // match template argument type
//             return hash<int>{}(i.hashKey());
//         }
//     };
// }
