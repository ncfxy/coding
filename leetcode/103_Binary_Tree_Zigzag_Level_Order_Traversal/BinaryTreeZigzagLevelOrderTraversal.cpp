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
    vector<vector<int> > zigzagLevelOrder(TreeNode *root)
    {
        vector<TreeNode *> buffer;
        buffer.push_back(root);
        vector<vector<int> > result;
        bool leftToRight = true;
        if(root == NULL){
            return result;
        }
        while(!buffer.empty()){
            vector<TreeNode *> newBuffer;
            vector<int> level;
            for (int i = buffer.size() - 1; i >= 0;i--){
                if(leftToRight){
                    if (buffer[i]->left != NULL)
                    {
                        newBuffer.push_back(buffer[i]->left);
                    }
                    if (buffer[i]->right != NULL)
                    {
                        newBuffer.push_back(buffer[i]->right);
                    }
                }else{
                    if (buffer[i]->right != NULL)
                    {
                        newBuffer.push_back(buffer[i]->right);
                    }
                    if (buffer[i]->left != NULL)
                    {
                        newBuffer.push_back(buffer[i]->left);
                    }
                }
                level.push_back(buffer[i]->val);
            }
            result.push_back(level);
            buffer = newBuffer;
            leftToRight = !leftToRight;
        }
        return result;
    }
    
};

int main()
{
    Solution so;
    TreeNode *t3 = new TreeNode(3);
    TreeNode *t9 = new TreeNode(9);
    TreeNode *t20 = new TreeNode(20);
    TreeNode *t15 = new TreeNode(15);
    TreeNode *t7 = new TreeNode(7);
    t3->left = t9;
    t3->right = t20;
    t20->left = t15;
    t20->right = t7;
    so.zigzagLevelOrder(t3);
    system("pause");
    return 0;
}
