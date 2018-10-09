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
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> result;
        inorderTraversalInner(root, result);
        return result;
    }

    void inorderTraversalInner(TreeNode *root, vector<int> &result){
        if(root != NULL){
            inorderTraversalInner(root->left, result);
            result.push_back(root->val);
            inorderTraversalInner(root->right, result);
        }
    }

};

int main()
{
    Solution so;
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(3);
    a.right = &b;
    b.left = &c;
    vector<int> result = so.inorderTraversal(&a);
    for (int i = 0; i < result.size();i++){
        cout << result[i] << endl;
    }

        system("pause");
    return 0;
}
