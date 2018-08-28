#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

class Solution
{
  public:
    vector<int> searchRange(vector<int> &nums, int target)
    {
        vector<int> result;
        vector<int> none;
        none.push_back(-1);
        none.push_back(-1);
        if (nums.empty())
        {
            return none;
        }
        int left = 0, right = nums.size() - 1;
        while(left < right){
            int mid = (left + right) / 2;
            if(nums[mid] >= target){
                right = mid;
            }else {
                left = mid+1;
            }
        }
        if(nums[right] != target){
            return none;
        }
        result.push_back(right);
        left = 0, right = nums.size() - 1;
        while(left < right-1){
            int mid = (left + right) / 2;
            if(nums[mid] <= target){
                left = mid ;
            }else {
                right = mid - 1;
            }
        }
        if(nums[right] == target){
            result.push_back(right);
        }else{
            result.push_back(left);
        }
        return result;
    }
};

int main()
{
    Solution so;
    vector<int> nums;
    nums.push_back(5);
    nums.push_back(7);
    nums.push_back(7);
    nums.push_back(8);
    nums.push_back(8);
    nums.push_back(10);
    vector<int> result = so.searchRange(nums, 8);
    for (int i = 0; i < result.size();i++){
        cout << result[i] << endl;
    }
    system("pause");
    return 0;
}

