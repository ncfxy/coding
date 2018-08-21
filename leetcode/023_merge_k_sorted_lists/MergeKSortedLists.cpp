#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL){}
};

class Solution{
public:
  ListNode *mergeKLists(vector<ListNode *> &lists)
  {
      int n = lists.size();
      if(n == 0)
          return NULL;
      for (int step = 1; step < n;step <<= 1){
          for (int i = 0; i < n - step;i += (step << 1)){
              lists[i] = mergeTwoLists(lists[i], lists[i + step]);
          }
      }
      return lists[0];
  }

  ListNode *mergeTwoLists(ListNode* node1, ListNode* node2){
      if(node1 == NULL){
          return node2;
      }
      if(node2 == NULL){
          return node1;
      }
      if(node1->val < node2->val){
          node1->next = mergeTwoLists(node1->next, node2);
          return node1;
      }else {
          node2->next = mergeTwoLists(node1, node2->next);
          return node2;
      }
  }
};

int main(){
    Solution so;
    return 0;
}