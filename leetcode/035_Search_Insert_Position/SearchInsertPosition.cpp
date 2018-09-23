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
    int searchInsert(vector<int> &nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        while(left <= right){
            int mid = (left + right) >> 1;
            if(nums[mid] == target){
                return mid;
            }else if(nums[mid] < target){
                left = mid + 1;
            }else {
                right = mid - 1;
            }
        }
        return left;
    }
};

int main()
{
    Solution so;
    vector<int> ve;
    ve.push_back(1);
    ve.push_back(3);
    ve.push_back(5);
    ve.push_back(6);
    cout << so.searchInsert(ve, 5) << endl;
    cout << so.searchInsert(ve, 2) << endl;
    cout << so.searchInsert(ve, 7) << endl;
    cout << so.searchInsert(ve, 0) << endl;

    system("pause");
    return 0;
}

