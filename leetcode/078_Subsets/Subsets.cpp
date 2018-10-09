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
    vector<vector<int> > subsets(vector<int> &nums)
    {
        vector<vector<int> > result;
        vector<int> buffer;
        find(nums, 0, buffer, result);
        return result;
    }

    void find(vector<int> &nums, int current, vector<int> buffer, vector<vector<int> > &result){
        if(current == nums.size()){
            result.push_back(buffer);
            return;
        }
        find(nums, current + 1, buffer, result);
        buffer.push_back(nums[current]);
        find(nums, current + 1, buffer, result);
        buffer.pop_back();
    }
};

int main()
{
    Solution so;
    int a[3] = {1,2,3};
    vector<int> ve(a, a + 3);
    vector<vector<int> > result = so.subsets(ve);
    for (int i = 0; i < result.size();i++){
        for (int j = 0; j < result[i].size();j++){
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
        system("pause");
    return 0;
}
