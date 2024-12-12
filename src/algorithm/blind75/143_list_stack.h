#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>
using namespace std;

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
    void reorderList(ListNode* head) {
        stack<ListNode*> s;
        ListNode* curr = head;
        // evert two elements
        while (curr) {
            s.push(curr);
            curr = curr->next;
        }

        curr = head;
        while (!s.empty()) {
            auto n = s.top();
            s.pop();

            auto tmp = curr->next;
            // [1,2,3,4]: meets 
            // last comparison is: n = 3, tmp = 3; n == tmp

            // [1, 2, 3, 4, 5]:
            // after one reorder op,  
            // [1, 5, 2, 3, 4]
            // after 2nd reorder
            // [1, 5, 2, 4, 3]: 3 --> 4 and 4 --> 3, meet  n->next == tmp,

            // last comparision, tmp = 2, n = 3, 

            if (n == tmp || n->next == tmp) {
                // 结束条件，链表节点数为奇数或偶数时均适用

                // only the 2nd to the last node in the original node needs reset next to null, becomes the new tail
                n->next = nullptr;
                break;
            }

            curr->next = n;
            n->next = tmp;
            curr = tmp;
        }
    }
};

class Solution {
public:
    void reorderList(ListNode* head) {
        stack<ListNode*> stk;
        // 先把所有节点装进栈里，得到倒序结果
        ListNode* p = head;
        while (p != nullptr) {
            stk.push(p);
            p = p->next;
        }

        p = head;
        while (p != nullptr) {
            // 链表尾部的节点
            ListNode* lastNode = stk.top();
            stk.pop();
            ListNode* next = p->next;
            // odd || even
            if (lastNode == next || lastNode->next == next) {
                // 结束条件，链表节点数为奇数或偶数时均适用
                lastNode->next = nullptr;
                break;
            }
            p->next = lastNode;
            lastNode->next = next;
            p = next;
        }
    }
};