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
    void flatten(TreeNode* root) {
        if(root == NULL){
            return;
        }
        TreeNode* rightChild = root->right;
        bool hasLeft = false;
        if(root->left != NULL){
            hasLeft = true;
            root->right = root->left;
            root->left = NULL;
            flatten(root->right);
        }
        if(rightChild != NULL){
            while(root->right != NULL && hasLeft){
                root = root->right;
            }
            root->right = rightChild;
            flatten(rightChild);
        }
        return;
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
    TreeNode* t1 = new TreeNode(1);
    TreeNode* t2 = new TreeNode(2);
    TreeNode* t3 = new TreeNode(3);
    TreeNode* t4 = new TreeNode(4);
    TreeNode* t5 = new TreeNode(5);
    TreeNode* t6 = new TreeNode(6);
    t1->left = t2;
    t2->left = t3;
    t2->right = t4;
    t1->right = t5;
    t5->right = t6;
    so.flatten(t1);
    return 0;
}
