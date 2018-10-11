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
    
    int maxProfit(vector<int>& prices) {
        if(prices.size() < 2){
            return 0;
        }
        int maxProfit = 0;
        int minBuyPrice = prices[0];
        for(int i = 1;i < prices.size();i++){
            if(prices[i] - minBuyPrice > maxProfit){
                maxProfit = prices[i] - minBuyPrice;
            }
            if(prices[i] < minBuyPrice){
                minBuyPrice = prices[i];
            }
        }
        return maxProfit;
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
    int a[6] = {7,1,5,3,6,4};
    vector<int> ve(a,a+6);
    cout << so.maxProfit(ve) << endl;
    
    return 0;
}
