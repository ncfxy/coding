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
    bool isSymmetric(TreeNode *root)
    {
        if(root == NULL)
            return true;
        return isTwoSymmetric(root->left, root->right);
    }

    bool isTwoSymmetric(TreeNode* leftNode, TreeNode* rightNode)
    {
        if((leftNode == NULL && rightNode != NULL) || (leftNode != NULL && rightNode == NULL)){
            return false;
        }
        if(leftNode == NULL && rightNode == NULL){
            return true;
        }
        if(leftNode->val != rightNode->val){
            return false;
        }
        if(!isTwoSymmetric(leftNode->left, rightNode->right) || !isTwoSymmetric(leftNode->right, rightNode->left)){
            return false;
        }
        return true;
    }
};

int main()
{
    Solution so;
    system("pause");
    return 0;
}
