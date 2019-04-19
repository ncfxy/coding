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
    bool hasPathSum(TreeNode *root, int sum)
    {
        if(root == NULL){
            return false;
        }
        if(root->left == NULL && root->right == NULL){
            return root->val == sum;
        }
        int newSum = sum - root->val;
        return hasPathSum(root->left, newSum) || hasPathSum(root->right, newSum);
    }
};

int main()
{
    Solution so;
    system("pause");
    return 0;
}
