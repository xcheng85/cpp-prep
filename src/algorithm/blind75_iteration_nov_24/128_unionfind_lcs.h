// nums = [100,4,200,1,3,2]
// the order of input does not matter
// o(n) is required. so sorting is out of the way

// how to handle duplicated numbers ? ignore

// union set merge process

// hashmap for look up neighboring number
// and then just merge

// unionset needs 0, n-1 consecutive
// handle duplicates

#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class UnionSet
{
public:
    UnionSet(int n) : _parents(n, -1), _setSize(n, 1)
    //, _setCount{n}
    {
        for (int i = 0; i < n; ++i)
        {
            _parents[i] = i;
        }
    }

    void merge(int n1, int n2)
    {
        int p1 = parents(n1);
        int p2 = parents(n2);
        if (p1 == p2)
        {
            return;
        }
        _parents[p2] = p1;
        _setSize[p1] += _setSize[p2];

        // if (_setSize[p1] > _setSize[p2])
        // {
        //     _parents[p2] = p1;
        //     _setSize[p1] += _setSize[p2];
        // }
        // else
        // {
        //     _parents[p1] = p2;
        //     _setSize[p2] += _setSize[p1];
        // }
        // --_setCount;
    }

    int parents(int nodeIndex)
    {
        int curr = nodeIndex;
        while (curr != _parents[curr])
        {
            curr = _parents[curr];
        }
        return curr;
    }

    // inline int setCount() const
    // {
    //     return _setCount;
    // }

    int getLargetSetSize()
    {
        if (_setSize.size() > 0)
            return *std::max_element(_setSize.begin(), _setSize.end());
        return 0;
        // int res = 0;
        // // only consider route
        // for (int i = 0; i < _setSize.size(); i++)
        // {
        //     res = max(res, _setSize[i]);
        // }

        // return res;
    }

private:
    vector<int> _parents;
    // for a more balanced tree tructure
    vector<int> _setSize;
    // int _setCount;
};

class Solution
{
public:
    using VALUE = int;
    using SETIDX = int;
    int longestConsecutive(vector<int> &nums)
    {
        UnionSet us(nums.size());
        // need to be able to retrieve the nodeIndex from the value to access the unionset
        // duplicates automatically only select the first one run into.
        unordered_map<VALUE, SETIDX> hm;

        for (int setId = 0; setId < nums.size(); setId++)
        {
            int value = nums[setId];
            // must ignore the duplicates.
            if (hm.count(value))
                continue;
            if (hm.count(value - 1))
            {
                int neightboringSetId = hm[value - 1];
                us.merge(setId, neightboringSetId);
            }
            if (hm.count(value + 1))
            {
                int neightboringSetId = hm[value + 1];
                us.merge(setId, neightboringSetId);
            }
            hm.insert(make_pair(nums[setId], setId));
        }

        return us.getLargetSetSize();
    }
};