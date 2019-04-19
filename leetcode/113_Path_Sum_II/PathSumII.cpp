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
    
    vector<vector<int> > pathSum(TreeNode *root, int sum)
    {
        vector<vector<int> > result;
        vector<int> buffer;
        if(root == NULL){
            return result;
        }
        traversalTree(root, sum, buffer, result);
        return result;
    }

    void traversalTree(TreeNode *root, int sum, vector<int> &buffer, vector<vector<int> > &result){
        if(root == NULL){
            return;
        }
        int leftSum = sum - root->val;
        buffer.push_back(root->val);
        if(root->left == NULL && root->right == NULL){
            if(leftSum == 0){
                result.push_back(buffer);
            }
        }else{
            traversalTree(root->left, leftSum, buffer, result);
            traversalTree(root->right, leftSum, buffer, result);
        }
        buffer.pop_back();
        return;
    }
};

int main()
{
    Solution so;

    system("pause");
    return 0;
}
