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
    int result;
    int maxPathSum(TreeNode *root)
    {
        result = 0x80000000;
        traversalTree(root);
        return result;
    }

    int traversalTree(TreeNode *root){
        if(root == NULL){
            return 0;
        }
        int left = traversalTree(root->left);
        int right = traversalTree(root->right);
        left = left < 0 ? 0 : left;
        right = right < 0 ? 0 : right;
        if(root->val + left + right > result){
            result = root->val + left + right;
        }
        return root->val + max(left, right);
    }
};

int main()
{
    Solution so;
    int a = 0x7fffffff;
    int b = 0x80000000;
    cout << a << endl;
    cout << b << endl;
    system("pause");
    return 0;
}
