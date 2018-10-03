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
    int minDepth(TreeNode* root) {
        if(root == NULL){
            return 0;
        }
        if(root->left == NULL && root->right == NULL){
            return 1;
        }
        int leftMinDepth = minDepth(root->left);
        int rightMinDepth = minDepth(root->right);
        if(leftMinDepth == 0){
            return rightMinDepth + 1;
        }
        if(rightMinDepth == 0){
            return leftMinDepth + 1;
        }
        return min(leftMinDepth, rightMinDepth) + 1;
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
