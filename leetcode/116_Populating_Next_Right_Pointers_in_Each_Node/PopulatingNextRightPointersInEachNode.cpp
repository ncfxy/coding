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

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:
    
    void connect(TreeLinkNode *root) {
        if(root == NULL){
            return;
        }
        TreeLinkNode* currentFirst;
        currentFirst = root;
        while(currentFirst != NULL){
            TreeLinkNode *tmp = currentFirst;
            while(tmp != NULL){
                if(tmp->left != NULL && tmp->right != NULL){
                    tmp->left->next = tmp->right;
                    if(tmp->next != NULL){
                        tmp->right->next = tmp->next->left;
                    }
                }
                tmp = tmp->next;
            }
            currentFirst = currentFirst->left;
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
    TreeLinkNode* t1 = new TreeLinkNode(1);
    TreeLinkNode* t2 = new TreeLinkNode(2);
    TreeLinkNode* t3 = new TreeLinkNode(3);
    TreeLinkNode* t4 = new TreeLinkNode(4);
    TreeLinkNode* t5 = new TreeLinkNode(5);
    TreeLinkNode* t6 = new TreeLinkNode(6);
    TreeLinkNode * t7 = new TreeLinkNode(7);
    t1->left = t2;
    t1->right = t3;
    t2->left = t4;
    t2->right = t5;
    t3->left = t6;
    t3->right = t7;
    so.connect(t1);
    return 0;
}
