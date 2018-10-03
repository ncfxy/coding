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

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int size = nums.size() - 1;
        return sortedArrayToBSTInner(nums, 0, size);
    }
    
    TreeNode* sortedArrayToBSTInner(vector<int>& nums, int start, int end){
        if(start > end){
            return NULL;
        }
        if(start == end){
            TreeNode* newNode = new TreeNode(nums[start]);
            return newNode;
        }
        int mid = (start + end) / 2;
        TreeNode* newNode = new TreeNode(nums[mid]);
        newNode->left = sortedArrayToBSTInner(nums, start, mid-1);
        newNode->right = sortedArrayToBSTInner(nums, mid + 1, end);
        return newNode;
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
    int a[] = {1,2,3,4,5};
    vector<int> ve(a,a+5);
    TreeNode* root = so.sortedArrayToBST(ve);
    preOrderTravelsal(root);
    return 0;
}
