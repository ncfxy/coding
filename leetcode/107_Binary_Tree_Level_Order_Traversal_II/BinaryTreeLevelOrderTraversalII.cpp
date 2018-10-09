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
    vector<vector<int>> levelOrderBottom(TreeNode *root)
    {
        vector<vector<int>> result = levelOrder(root);
        reverse(result.begin(), result.end());
        return result;
    }
    vector<vector<int> > levelOrder(TreeNode *root)
    {
        vector<TreeNode *> buffer;
        buffer.push_back(root);
        vector<vector<int> > result;
        if (root == NULL)
        {
            return result;
        }
        while (!buffer.empty())
        {
            vector<TreeNode *> newBuffer;
            vector<int> level;
            for (int i = 0; i < buffer.size(); i++)
            {
                if (buffer[i]->left != NULL)
                {
                    newBuffer.push_back(buffer[i]->left);
                }
                if (buffer[i]->right != NULL)
                {
                    newBuffer.push_back(buffer[i]->right);
                }
                level.push_back(buffer[i]->val);
            }
            result.push_back(level);
            buffer = newBuffer;
        }
        return result;
    }
};

int main()
{
    Solution so;
    system("pause");
    return 0;
}
