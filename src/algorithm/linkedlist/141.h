/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        auto slow = head;
        auto fast = head;

        if(fast && fast->next && fast->next->next) {
            fast = fast->next->next;
        } else {
            return false;
        }

        while(fast != slow && fast && fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;
        }

        return fast == slow;
    }
};