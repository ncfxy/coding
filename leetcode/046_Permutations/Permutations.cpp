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
    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<bool> bo;
        vector<int> buffer;
        for (int i = 0; i < nums.size(); i++)
        {
            bo.push_back(true);
        }
        vector<vector<int>> result;
        dfsPermute(nums, bo, result, buffer);
        return result;
    }

    void dfsPermute(vector<int> &nums, vector<bool> bo, vector<vector<int>> &result, vector<int> &buffer)
    {
        if (buffer.size() == nums.size())
        {
            vector<int> ve;
            ve.insert(ve.begin(), buffer.begin(), buffer.end());
            result.push_back(ve);
            return;
        }
        for (int i = 0; i < nums.size(); i++)
        {
            if (bo[i])
            {
                bo[i] = false;
                buffer.push_back(nums[i]);
                dfsPermute(nums, bo, result, buffer);
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
    nums.push_back(3);
    vector<vector<int>> result = so.permute(nums);
    for (int i = 0; i < result.size(); i++)
    {
        for (int j = 0; j < result[i].size(); j++)
        {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
    system("pause");
    return 0;
}
