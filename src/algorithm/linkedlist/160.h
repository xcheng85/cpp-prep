
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
    // pointer address cache
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        set<ListNode*> cache;
        auto curr = headA;
        while(curr) {
            cache.insert(curr);
            curr=curr->next;
        }

        curr = headB;
        while(curr) {
            if(cache.find(curr) != cache.end()) {
                return curr;
            }
             curr=curr->next;
        }
        return nullptr;
        
    }
};