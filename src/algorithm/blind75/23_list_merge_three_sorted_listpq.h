#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>

using namespace std;

// 1. list -> dummyNode


struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        ListNode dummy;
        auto curr = &dummy;

        // ascending, minQueue
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        // already sorted, smallest, header of each
        for (size_t i = 0; i < lists.size(); ++i)
        {
            if (lists[i])
                pq.emplace(pair{lists[i]->val, i});
        }

        while (!pq.empty())
        {
            auto listId = pq.top().second;
            // cout << pq.top().first << ", " << pq.top().second << endl;
            pq.pop();
            auto tmp = lists[listId];
            // write to the output list
            curr->next = lists[listId];
            curr = curr->next;

            lists[listId] = lists[listId]->next;
            if (lists[listId])
            {
                pq.emplace(pair{lists[listId]->val, listId});
            }
        }
        return dummy.next;
    }
};