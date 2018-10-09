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
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        return buildSubTree(inorder, postorder, inorder.size(), 0, 0);
    }

    TreeNode *buildSubTree(vector<int> &inorder, vector<int> &postorder, int length, int inStart, int postStart){
        if(length <= 0){
            return NULL;
        }
        int currentNodeValue = postorder[postStart + length - 1];
        int nodeInOrderLocation;
        if (length == 1)
        {
            TreeNode *currentNode = new TreeNode(currentNodeValue);
            return currentNode;
        }
        for (int i = inStart; i < inStart + length; i++)
        {
            if (inorder[i] == currentNodeValue)
            {
                nodeInOrderLocation = i;
            }
        }
        TreeNode *currentNode = new TreeNode(currentNodeValue);
        int leftLength = nodeInOrderLocation - inStart;
        int rightLength = length - leftLength - 1;
        currentNode->left = buildSubTree(inorder, postorder, leftLength, inStart, postStart);
        currentNode->right = buildSubTree(inorder, postorder, rightLength, nodeInOrderLocation + 1, postStart + leftLength);
        return currentNode;
    }
};

int main()
{
    Solution so;
    system("pause");
    return 0;
}
