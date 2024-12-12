// words = ["wrt","wrf","er","ett","rftt"]: lexicographically increasing order ---> tell you about some order. like canFinishCourse
// If this claim is incorrect, and the given arrangement of string in words cannot correspond to any order of letters, return "".
// This told me "CanFinishCourse == false"



//  words = ["wrt","wrf","er","ett","rftt"]


// how to model nodes and edges from this question ? 
// words[i] consists of only lowercase English letters. --> only 26 nodes
// model directed edges is the first key point


// two special cases: 

// 1. [abc, ab] is a "", no result
// 2. [z, z] is good result: z 

#include <vector>
#include <string>
#include <numeric>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    string alienOrder(vector<string>& words) {
        // "abcdghijklmnopqsuvwxyzertf"
        // rule out non-exist char
        unordered_set<int> cache;
        for (const auto& w : words) {
            for (const auto& c : w) {
                cache.insert(c - 'a');
            }
        }

        // adj list
        vector<vector<int>> adjList(26, vector<int>());
        // in-degree for topology sorting
        vector<int> inDegrees(26, 0);
     
        for (int i = 1; i < words.size(); i++) {
            const auto& w1 = words[i - 1];
            const auto& w2 = words[i];
            bool canCreateDirectedEdge = false;

            // 1. min length
            // 2. skip the same char
            // 3. the first difference decide the order
            // 4. could be the case that cannto have result: ab and abc

            for (int j = 0; j < std::min(w1.length(), w2.length()); j++) {
                if (w1[j] == w2[j])
                    continue;
                // directed edge: w1[j] --> w2[j]
                // cout << "find directed edge: " << w1[j] << "-->" << w2[j] <<
                // endl;
                adjList[w1[j] - 'a'].emplace_back(w2[j] - 'a');
                ++inDegrees[w2[j] - 'a'];
                // key once find igore the rest
                canCreateDirectedEdge = true;
                break;
            }
            // 1. [abc, ab] is a "", no result
            // w1.length() > w2.length() is incorrect it will miss the case [ab, abc] which is legit
            if(!canCreateDirectedEdge && w1.length() > w2.length()){
                return "";
            }
        }
        // ready for sorting
        string res;
        queue<int> zeroInDegreeNodeIndex;

        for (int nodeIndex = 0; nodeIndex < inDegrees.size(); nodeIndex++) {
            if (inDegrees[nodeIndex] == 0) {
                if (cache.find(nodeIndex) != cache.end()) {
                    cout << nodeIndex << endl;
                    zeroInDegreeNodeIndex.emplace(nodeIndex);
                }
            }
        }

        while (!zeroInDegreeNodeIndex.empty()) {
            const auto currentZeroInDegreeNodeIndex =
                zeroInDegreeNodeIndex.front();
            zeroInDegreeNodeIndex.pop();
            res.push_back(currentZeroInDegreeNodeIndex + 'a');
            for (const auto& neighboringNodeIndex :
                 adjList[currentZeroInDegreeNodeIndex]) {
                --inDegrees[neighboringNodeIndex];
                if (inDegrees[neighboringNodeIndex] == 0) {
                    zeroInDegreeNodeIndex.emplace(neighboringNodeIndex);
                }
            }
        }
        if (res.length() == cache.size()) {
            return res;
        }
        return "";
    }
};