#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
  public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        ListNode *head = new ListNode(0);
        ListNode *tmp = head;
        while(l1 != NULL && l2 != NULL){
            if(l1->val < l2->val){
                tmp->next = l1;
                l1 = l1->next;
            }else {
                tmp->next = l2;
                l2 = l2->next;
            }
            tmp = tmp->next;
        }
        if (l1 == NULL)
        {
            tmp->next = l2;
        }
        if (l2 == NULL)
        {
            tmp->next = l1;
        }
        tmp = head->next;
        delete head;
        return tmp;
    }

    ListNode *mergeTwoLists_2(ListNode *l1, ListNode *l2)
    {
        if (l1 == NULL)
            return l2;
        if (l2 == NULL)
            return l1;
        if (l1->val < l2->val)
        {
            l1->next = mergeTwoLists_2(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists_2(l1, l2->next);
            return l2;
        }
    }
};

int main()
{
    Solution so;
    ListNode *node1 = new ListNode(1);
    node1->next = new ListNode(2);
    node1->next->next = new ListNode(4);
    
    ListNode *node2 = new ListNode(1);
    node2->next = new ListNode(3);
    node2->next->next = new ListNode(4);
    ListNode *result = so.mergeTwoLists(node1, node2);
    while(result != NULL){
        cout << result->val << endl;
        result = result->next;
    }
    system("pause");
    return 0;
}