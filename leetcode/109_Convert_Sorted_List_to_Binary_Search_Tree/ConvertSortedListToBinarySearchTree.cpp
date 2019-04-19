#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
  public:
    ListNode *current = NULL;

    TreeNode *buildTree(int start, int end){
        if(start > end){
            return NULL;
        }
        int mid = (start + end) / 2;
        TreeNode *left = buildTree(start, mid - 1);
        TreeNode *root = new TreeNode(current->val);
        current = current->next;
        root->left = left;
        root->right = buildTree(mid + 1, end);
        return root;
    }

    TreeNode *sortedListToBST(ListNode *head)
    {
        if(head == NULL){
            return NULL;
        }
        int len = 0;
        ListNode *tmp = head;
        current = head;
        while(tmp != NULL){
            len++;
            tmp = tmp->next;
        }
        return buildTree(0, len - 1);
    }
};

int main()
{
    Solution so;
    system("pause");
    return 0;
}
