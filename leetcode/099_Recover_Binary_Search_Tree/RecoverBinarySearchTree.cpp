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
    TreeNode *first, *second;
    TreeNode *pre;
    bool findFirst, findSecond;
    void recoverTree(TreeNode *root)
    {
        findFirst = false;
        findSecond = false;
        pre = NULL;
        midTravelTree(root);
        if(!findSecond){
            int tmp = second->val;
            second->val = first->val;
            first->val = tmp;
        }
    }

    void midTravelTree(TreeNode *root){
        if(root == NULL){
            return;
        }
        midTravelTree(root->left);
        visitNode(root);
        midTravelTree(root->right);
    }

    void visitNode(TreeNode* node){
        if(pre != NULL && pre->val > node->val){
            if(findFirst){
                second = node;
                int tmp = second->val;
                second->val = first->val;
                first->val = tmp;
                findSecond = true;
            }else{
                first = pre;
                second = node;
                findFirst = true;
            }
        }
        pre = node;
    }
};

int main()
{
    Solution so;
    TreeNode *t1 = new TreeNode(1);
    TreeNode *t2 = new TreeNode(2);
    TreeNode *t3 = new TreeNode(3);
    TreeNode *t4 = new TreeNode(4);
    t3->left = t1;
    t3->right = t4;
    t4->left = t2;
    so.recoverTree(t3);
    system("pause");
    return 0;
}
