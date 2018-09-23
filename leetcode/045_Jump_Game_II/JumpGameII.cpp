#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

class Solution
{
  public:
    int jump(vector<int> &nums)
    {
        int size = nums.size();
        int lastUpdateIndex = 0;
        vector<int> dp(size, size);
        dp[0] = 0;
        for (int i = 0; i < size; i++)
        {
            for (int j = lastUpdateIndex - i + 1; j <= nums[i] && i + j < size; j++)
            {
                dp[i + j] = min(dp[i + j], dp[i] + 1);
                lastUpdateIndex = max(lastUpdateIndex, i + j);
            }
        }
        return dp[size - 1];
    }
};

int main()
{
    Solution so;

    int a[5] = {2, 3, 1, 1, 4};
    vector<int> ve(a, a + 5);
    cout << so.jump(ve) << endl;
    system("pause");
    return 0;
}
