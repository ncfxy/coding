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
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
  public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        return buildSubTree(preorder, inorder, preorder.size(), 0, 0);
    }

    TreeNode *buildSubTree(vector<int> &preorder, vector<int> &inorder, int length, int preStart, int inStart)
    {
        if (length <= 0)
            return NULL;
        int currentNodeValue = preorder[preStart];
        int firstNodeInOrderLocation;
        if (length == 1)
        {
            TreeNode *currentNode = new TreeNode(currentNodeValue);
            return currentNode;
        }
        for (int i = inStart; i < inStart + length; i++)
        {
            if (inorder[i] == currentNodeValue)
            {
                firstNodeInOrderLocation = i;
            }
        }
        TreeNode *currentNode = new TreeNode(currentNodeValue);
        int leftLength = firstNodeInOrderLocation - inStart;
        int rightLength = length - leftLength - 1;
        currentNode->left = buildSubTree(preorder, inorder, leftLength, preStart + 1, inStart);
        currentNode->right = buildSubTree(preorder, inorder, rightLength, preStart + leftLength + 1, firstNodeInOrderLocation + 1);
        return currentNode;
    }
};

int main()
{
    Solution so;
    system("pause");
    return 0;
}
