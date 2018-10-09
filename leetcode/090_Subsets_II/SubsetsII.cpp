#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Solution
{
  public:
    vector<vector<int> > subsetsWithDup(vector<int> &nums)
    {
        vector<vector<int> > result;
        vector<int> buffer;
        sort(nums.begin(), nums.end());
        dfs(nums, 0, result, buffer);
        return result;
    }

    void dfs(vector<int> &nums, int current, vector<vector<int> > &result, vector<int>  buffer){
        if(current >= nums.size()){
            result.push_back(buffer);
            return;
        }
        int currentValue = nums[current];
        int nextLocation = current + 1;
        while(nextLocation < nums.size() && nums[nextLocation] == currentValue){
            nextLocation++;
        }
        dfs(nums, nextLocation, result, buffer);
        for (int i = 0; i < nextLocation - current;i++)
        {
            buffer.push_back(currentValue);
            dfs(nums, nextLocation, result, buffer);
        }
    }
};

int main()
{
    Solution so;
    int a[3] = {1, 2, 2};
    vector<int> ve(a, a + 3);
    vector<vector<int> > result =    so.subsetsWithDup(ve);
    for (int i = 0; i < result.size();i++){
        for (int j = 0; j < result[i].size();j++){
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

        system("pause");
    return 0;
}
