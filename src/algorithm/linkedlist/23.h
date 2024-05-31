/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

// class CmpFunctor {
// public:
//     bool operator()(ListNode* n1, ListNode* n2) const {
//         return n1->val >= n2->val;
//     }
// };

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode dummy;
        auto curr = &dummy;

        // ascending
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for (size_t i = 0; i < lists.size(); ++i) {
            if(lists[i])
                pq.emplace(pair{lists[i]->val, i});
        }

        while (!pq.empty()) {
            auto listId = pq.top().second;
            cout << pq.top().first << ", " << pq.top().second<< endl;
            pq.pop();
            auto tmp = lists[listId];
            curr -> next = lists[listId]; 
            curr = curr->next;

            lists[listId] = lists[listId]->next;
            if(lists[listId]) {
                pq.emplace(pair{lists[listId]->val, listId});
            }
        }
        return dummy.next;
    }
};