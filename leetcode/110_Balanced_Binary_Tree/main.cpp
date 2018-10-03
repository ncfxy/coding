//
//  main.cpp
//  helloworld
//
//  Created by Xiangyu Fan on 2018/10/3.
//  Copyright © 2018年 Xiangyu Fan. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x):val(x), next(NULL){}
};

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(root == NULL){
            return true;
        }
        int height = getBalancedTreeHeight(root);
        if(height == -1){
            return false;
        }
        return true;
    }
    
    int getBalancedTreeHeight(TreeNode* root){
        if(root == NULL){
            return 0;
        }
        int leftHeight = getBalancedTreeHeight(root->left);
        int rightHeight = getBalancedTreeHeight(root->right);
        if(leftHeight == -1 || rightHeight == -1){
            return -1;
        }else{
            if(abs(leftHeight - rightHeight) > 1){
                return -1;
            }
            return max(leftHeight, rightHeight) + 1;
        }
    }
    
    
};

void preOrderTravelsal(TreeNode * root){
    if(root == NULL){
        cout << "null" << endl;
        return;
    }
    cout << root->val << endl;
    preOrderTravelsal(root->left);
    preOrderTravelsal(root->right);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution so;
    return 0;
}
