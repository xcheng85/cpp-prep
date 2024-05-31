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
    ListNode* middleNode(ListNode* head) {
        auto slow = head;
        auto fast = head;

        while(true) {
            if(fast->next && fast->next->next) {
                fast = fast->next->next;
                slow = slow->next;
            } else if(fast->next && !fast->next->next) {
                fast = fast -> next;
                slow = slow -> next;
            } else {
                break;
            }
        }
        return slow;
    }
};