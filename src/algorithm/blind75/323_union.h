#include <vector>
using namespace std;

class UnionSet
{
public:
    UnionSet(int n) : _parents(n, -1), _size(n, 1)
    {
        for (int i = 0; i < n; ++i)
        {
            // each one is in spearate set
            _parents[i] = i;
        }
        // initially, every node is in its own set
        _setCount = n;
    }

    void unionSets(int nodeIdx1, int nodeIdx2)
    {
        int p1 = parent(nodeIdx1);
        int p2 = parent(nodeIdx2);

        // unbalance
        // if(p1 != p2)
        //      _parents[p1] = p2;
        // already in one set, early return
        if (p1 == p2)
            return;

        if (_size[p1] > _size[p2])
        {
            //// 小树接到大树下面，较平衡
            _parents[p2] = p1;
            _size[p1] += _size[p2];
        }
        else
        {
            _parents[p1] = p2;
            _size[p2] += _size[p1];
        }
        --_setCount; // 两个分量合二为一
    }

    int parent(int nodeIdx)
    {
        int currentNodeIdx = nodeIdx;
        while (_parents[currentNodeIdx] != currentNodeIdx)
        {
            currentNodeIdx = _parents[currentNodeIdx];
        }
        return currentNodeIdx;
    }

    inline auto setCount() const{
        return _setCount;
    }

private:
    vector<int> _parents;
    vector<int> _size; // for balance of tree
    int _setCount;
};

class Solution
{
public:
    int countComponents(int n, vector<vector<int>> &edges)
    {
        UnionSet s(n);
        for(const auto& e : edges) {
            s.unionSets(e[0], e[1]);
        }
        return s.setCount();
    }
};