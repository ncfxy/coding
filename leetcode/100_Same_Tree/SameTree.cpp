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
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        if((p == NULL && q != NULL) ||(p != NULL && q == NULL)){
            return false;
        }
        if(p == NULL && q == NULL){
            return true;
        }
        if(p->val != q->val){
            return false;
        }
        if(!isSameTree(p->left, q->left) || !isSameTree(p->right, q->right)){
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
