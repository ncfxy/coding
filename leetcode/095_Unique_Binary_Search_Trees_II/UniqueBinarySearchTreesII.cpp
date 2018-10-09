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
    vector<TreeNode *> generateTrees(int n)
    {
        vector<TreeNode *> result;
        if(n < 1)
            return result;
        return dfs(1, n);
    }

    vector<TreeNode *> dfs(int start, int end){
        vector<TreeNode *> currentTree;
        if (start > end)
        {
            currentTree.push_back(NULL);
            return currentTree;
        }
        if(start == end){
            TreeNode *t = new TreeNode(start);
            currentTree.push_back(t);
            return currentTree;
        }
        for (int i = start; i <= end;i++){
            vector<TreeNode *> left = dfs(start, i - 1);
            vector<TreeNode *> right = dfs(i + 1, end);
            for (int leftIndex = 0; leftIndex < left.size();leftIndex++){
                for (int rightIndex = 0; rightIndex < right.size();rightIndex++){
                    TreeNode *newTree = new TreeNode(i);
                    newTree->left = copyTree(left[leftIndex]);
                    newTree->right = copyTree(right[rightIndex]);
                    currentTree.push_back(newTree);
                }
            }
            for (int leftIndex = 0; leftIndex < left.size();leftIndex++){
                deleteTree(left[leftIndex]);
            }
            for (int rightIndex = 0; rightIndex < right.size();rightIndex++){
                deleteTree(right[rightIndex]);
            }
        }
        return currentTree;
    }

    void deleteTree(TreeNode *root){
        if(root == NULL){
            return;
        }
        deleteTree(root->left);
        root->left = NULL;
        deleteTree(root->right);
        root->right = NULL;
        delete root;
    }

    TreeNode* copyTree(TreeNode *tree){
        if(tree == NULL){
            return NULL;
        }
        TreeNode *newTree = new TreeNode(tree->val);
        newTree->left = copyTree(tree->left);
        newTree->right = copyTree(tree->right);
        return newTree;
    }
};

void outputTree(TreeNode *root){
    if(root == NULL){
        cout << "null ";
    } else{
        cout << root->val << " ";
        outputTree(root->left);
        outputTree(root->right);
    }
}

int main()
{
    Solution so;
    vector<TreeNode *> result = so.generateTrees(3);
    for (int i = 0; i < result.size(); i++)
    {
        outputTree(result[i]);
        cout << endl;
    }
        system("pause");
    return 0;
}
