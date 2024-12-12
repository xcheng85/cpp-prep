// node and edge
// directed graph, multi source
// cyclic graph
// union set

#include <vector>
#include <queue>
using namespace std;

// class UnionSet
// {
// public:
//     UnionSet(int numNodes) : _parents(numNodes, 0) {
//         for(int i = 0; i < numNodes; i++) {
//             _parents[i] = i;
//         }
//     }

//     void merge(int node1, int node2) {
//         int p1 = getParent(node1);
//         int p2 = getParent(node2);

//         _parents[p2] = p1;
//     }

//     int getParent(int node) {
//         int curr = node;
//         while(_parents[curr] != curr) {
//             curr = _parents[curr];
//         }
//         return curr;
//     }

// private:
//     vector<int> _parents;
// };

// class Solution
// {
// public:
//     bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
//     {
//         UnionSet us(numCourses);

//         for(const auto& e : prerequisites) {
//             auto p1 = us.getParent(e[0]), p2 = us.getParent(e[1]);
//             if(p1 == p2) {
//                 // already have edge before
//                 return false;
//             }
//             us.merge(e[0], e[1]);
//         }
//         return true;
//     }
// };

// directed graph
// topology sort: in degree ds
// adj list is still needed.


class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // node index starts with 0;
        vector<int> inDegree(numCourses, 0);
        vector<vector<int>> adjList(numCourses, vector<int>());

        // build the adj list and in-degree
        // id
        for(const auto& e: prerequisites) {
            adjList[e[0]].emplace_back(e[1]);
            inDegree[e[1]]++;
        }

        // topology sort
        // source should be all the nodes that have 0 in-degree. 
        queue<int> zeroInDegrees;
        for(int nodeIdx = 0; nodeIdx < inDegree.size(); nodeIdx++) {
            if(inDegree[nodeIdx] == 0) {
                zeroInDegrees.emplace(nodeIdx);
            }
        }
        int numNodeProcessed = 0;
        while(!zeroInDegrees.empty()) {
            auto nodeIdx = zeroInDegrees.front();
            zeroInDegrees.pop();
            ++numNodeProcessed;
            for(const auto& neighborNodeIdx : adjList[nodeIdx]) {
                --inDegree[neighborNodeIdx];
                if(inDegree[neighborNodeIdx] == 0) {
                    zeroInDegrees.emplace(neighborNodeIdx);
                }
            }
        }

        return numNodeProcessed == numCourses;
    }
};