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
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode dummy;

        stack<ListNode*> s;
        
        auto curr = head;
        while(curr) {
            s.push(curr);
            curr = curr->next;
        }

        curr = &dummy;
        while(!s.empty()) {
            auto tmp = s.top();
            s.pop();
            // key: cut off original link
            tmp->next = nullptr;

            curr->next = tmp;
            curr = curr->next;
        }

        return dummy.next;
    }
};