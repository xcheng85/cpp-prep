
class UnionSet
{
public:
    UnionSet(int n)
        : _parents(n, -1),
          _setSize(n, 1),
          _setCount(n)
    {
        for (int i = 0; i < n; ++i)
        {
            _parents[i] = i;
        }
    }

    int parents(int nodeIndex)
    {
        int curr = nodeIndex;
        while(curr != _parents[curr]) {
            curr = _parents[curr];
        }
        return curr;
    }

    bool merge(int n1, int n2) {
        int p1 = parents(n1);
        int p2 = parents(n2);

        if(p1 == p2) {
            return false;
        }

        if(_setSize[p1] < _setSize[p2]) {
            _parents[p1] = p2;
            _setSize[p2] += _setSize[p1];
        } else {
            _parents[p2] = p1;
            _setSize[p1] += _setSize[p2];   
        }
        --_setCount;
        return true;
    }

    inline auto setCount() const{
        return _setCount;
    }
private:
    vector<int> _parents;
    vector<int> _setSize;
    int _setCount;
};

class Solution
{
public:
    bool validTree(int n, vector<vector<int>> &edges)
    {
        UnionSet us(n); 
        for(const auto& e: edges) {
            // already in the set
            if(!us.merge(e[0], e[1])){
                // duplicates
                return false;
            }
        }
        if(us.setCount() == 1) {
            return true;
        }
        return false;
    }
};