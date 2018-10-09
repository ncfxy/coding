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

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

class Solution
{
  public:
    bool isValidBST(TreeNode *root)
    {
        long long maxValue = 0x7fffffff;
        maxValue += 2;
        long long minValue = -maxValue;
        return dfsIsValidBST(root, minValue, maxValue);
    }

    bool dfsIsValidBST(TreeNode *root, long long minValue, long long maxValue){
        if(root == NULL){
            return true;
        }
        if(root->val <= minValue || root->val >= maxValue){
            return false;
        }
        return dfsIsValidBST(root->left, minValue, root->val) && dfsIsValidBST(root->right, root->val, maxValue);
    }
};

int main()
{
    Solution so;
    so.isValidBST(NULL);
    system("pause");
    return 0;
}
