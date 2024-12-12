#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>
using namespace std;

class UnionSet
{
public:
    UnionSet(int n) : _parents(n, -1), _setSize(n, 1), _setCount{n}
    {
        for (int i = 0; i < n; ++i)
        {
            _parents[i] = i;
        }
    }

    void unionSets(int n1, int n2)
    {
        int p1 = parents(n1);
        int p2 = parents(n2);
        if (p1 == p2)
        {
            return;
        }
        if (_setSize[p1] > _setSize[p2])
        {
            _parents[p2] = p1;
            _setSize[p1] += _setSize[p2];
        }
        else
        {
            _parents[p1] = p2;
            _setSize[p2] += _setSize[p1];
        }
        --_setCount;
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

    inline int setCount() const
    {
        return _setCount;
    }
    int getLargetSetSize()
    {
        int res = 0;
        // only consider route
        for (int i = 0; i < _setSize.size(); i++)
        {
            res = max(res, _setSize[i]);
        }

        return res;
    }

private:
    vector<int> _parents;
    vector<int> _setSize;
    int _setCount;
};

class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        // hashmap for look up neighboring number
        // unionset needs 0, n-1 consecutive
        // handle duplicates
        unordered_map<int, int> hashmap;
        // use index offset to represent set
        UnionSet unionset(nums.size());
        for (int i = 0; i < nums.size(); ++i)
        {
            // handle duplicates
            if(hashmap.count(nums[i])) {
                // ignroe duplicates
                continue;
            }

            // search both neighbors
            if (hashmap.count(nums[i] - 1))
            {
                unionset.unionSets(i, hashmap[nums[i] - 1]);
            }
            if (hashmap.count(nums[i] + 1))
            {
                unionset.unionSets(i, hashmap[nums[i] + 1]);
            }
            hashmap.insert(make_pair(nums[i], i));
        }
        return unionset.getLargetSetSize();
    }
};

// class Solution {
//     public int longestConsecutive(int[] nums) {
//         UF uf = new UF(nums.length);
//         // Map val to index in nums
//         Map<Integer, Integer> valToIndex = new HashMap<>();

//         for (int i = 0; i < nums.length; i++) {
//             if (valToIndex.containsKey(nums[i])) {
//                 continue;
//             }

//             if (valToIndex.containsKey(nums[i] - 1)) {
//                 uf.union(i, valToIndex.get(nums[i] - 1));
//             }

//             if (valToIndex.containsKey(nums[i] + 1)) {
//                 uf.union(i, valToIndex.get(nums[i] + 1));
//             }

//             valToIndex.put(nums[i], i);
//         }

//         return uf.getLargetComponentSize();
//     }

//     class UF {
//         private int[] parent;
//         private int[] size;

//         public UF(int n) {
//             parent = new int[n];
//             size = new int[n];
//             for (int i = 0; i < n; i++) {
//                 parent[i] = i;
//                 size[i] = 1;
//             }
//         }

//         public void union(int x, int y) { // connected if consecutive
//             int rootX = find(x);
//             int rootY = find(y);
//             if (rootX != rootY) {
//                 parent[rootX] = rootY;
//                 size[rootY] += size[rootX];
//             }
//         };

//         private int find(int x) {
//             if (parent[x] == x) {
//                 return x;
//             }

//             return parent[x] = find(parent[x]);
//         };

//         public int getLargetComponentSize() {
//             int maxSize = 0;
//             for (int i = 0; i < parent.length; i++) {
//                 if (parent[i] == i && size[i] > maxSize) {
//                     maxSize = size[i];
//                 }
//             }

//             return maxSize;
//         }
//     }
// }