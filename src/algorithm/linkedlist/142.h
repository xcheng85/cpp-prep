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
    ListNode* detectCycle(ListNode* head) {
        auto slow = head;
        auto fast = head;

        while(true) {
            if(fast && fast->next && fast -> next->next) {
                fast = fast->next->next;
                slow = slow -> next; 

                if(fast == slow) {
                    break;
                }

            } else {
                break;
            }
        }
        // condition for loop
        if(fast == slow && fast && fast -> next != nullptr && fast -> next->next != nullptr) {
            // draw the figure, and next meeting pointer
            slow = head;

            // same speed
            while(slow != fast) {
                slow = slow -> next;
                fast = fast->next;
            }
            return slow;

        } else {
            return nullptr;
        }
    }
};