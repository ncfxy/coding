#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Solution
{
  public:
    vector<vector<int> > permuteUnique(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<bool> bo;
        vector<int> buffer;
        for (int i = 0; i < nums.size();i++){
            bo.push_back(true);
        }
        vector<vector<int> > result;
        dfsPermuteUnique(nums, bo, result, buffer);
        return result;
    }
    void dfsPermuteUnique(vector<int> &nums, vector<bool> &bo, vector<vector<int> > & result, vector<int> &buffer){
        if(buffer.size() == nums.size()){
            vector<int> ve;
            ve.insert(ve.begin(), buffer.begin(), buffer.end());
            result.push_back(ve);
            return;
        }
        for (int i = 0; i < nums.size(); i++)
        {
            if(i > 0 && nums[i] == nums[i-1] && bo[i-1]){
                continue;
            }
            if (bo[i])
            {
                bo[i] = false;
                buffer.push_back(nums[i]);
                dfsPermuteUnique(nums, bo, result, buffer);
                buffer.pop_back();
                bo[i] = true;
            }
        }
    }
};

int main()
{
    Solution so;
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(1);
    vector<vector<int> > result = so.permuteUnique(nums);
    for (int i = 0; i < result.size();i++){
        for (int j = 0; j < result[i].size();j++){
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
        system("pause");
    return 0;
}
