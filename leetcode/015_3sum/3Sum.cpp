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
    
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        int size = (int)nums.size();
        for(int i = 0;i < size - 2;i++){
            if(i > 0 && nums[i] == nums[i-1]){
                continue;
            }
            int start = i + 1, end = size - 1;
            while(start < end){
                if(nums[start] + nums[end] + nums[i] == 0){
                    vector<int> tmp;
                    tmp.push_back(nums[i]);
                    tmp.push_back(nums[start]);
                    tmp.push_back(nums[end]);
                    result.push_back(tmp);
                    while(start < end && nums[start] == nums[start+1])start++;
                    start++;
                    while(start < end && nums[end] == nums[end-1])end--;
                    end--;
                }else if(nums[start] + nums[end] + nums[i] < 0){
                    start++;
                }else{
                    end--;
                }
            }
        }
        return result;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution so;
    vector<int> ve = {-2,0,0,2,2};
    vector<vector<int>> result = so.threeSum(ve);
    for(int i = 0;i < result.size();i++){
        for(int j = 0;j < result[i].size();j++){
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
    cout << "haha" << endl;
    return 0;
}
