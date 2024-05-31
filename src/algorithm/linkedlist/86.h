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
    ListNode* partition(ListNode* head, int x) {
        ListNode s;
        ListNode ge;

        auto currS = &s;
        auto currGE = &ge;

        auto curr = head;
        while (curr) {
            if (curr->val < x) {
                currS->next = curr;
                currS = currS->next;
            } else {
                currGE->next = curr;
                currGE = currGE->next;
            }
            auto tmp = curr->next;
            curr->next = nullptr;
            curr = tmp;
        }

        currS->next = ge.next;
        return s.next;
    }
};