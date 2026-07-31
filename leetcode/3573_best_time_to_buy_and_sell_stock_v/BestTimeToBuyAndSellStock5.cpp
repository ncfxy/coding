#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  long long maximumProfit(vector<int> &prices, int k) {
    if (prices.empty()) {
      return 0;
    }
    int n = prices.size();
    k = min(k, n / 2);
    vector<vector<vector<long long>>> dp(
        n, vector<vector<long long>>(k + 1, vector<long long>(3, 0)));
    dp[0][0][0] = 0;
    dp[0][0][1] = -prices[0];
    dp[0][0][2] = 0;
    for (int j = 1; j <= k; j++) {
      dp[0][j][0] = 0;
      dp[0][j][1] = -prices[0];
      dp[0][j][2] = prices[0];
    }

    for (int i = 1; i < n; i++) {
      for (int j = 1; j <= k; j++) {
        dp[i][j][0] = max(dp[i - 1][j][0], max(dp[i - 1][j][1] + prices[i],
                                               dp[i - 1][j][2] - prices[i]));
        dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j-1][0] - prices[i]);
        dp[i][j][2] = max(dp[i - 1][j][2], dp[i - 1][j-1][0] + prices[i]);
      }
    }
    return dp[n - 1][k][0];
  }
};

int main() {
  Solution solution;
  //   输入: prices = [1,7,9,8,2], k = 2
  // 输出: 14
  vector<int> prices = {1, 7, 9, 8, 2};
  cout << solution.maximumProfit(prices, 2) << endl;

  //   输入: prices = [12,16,19,19,8,1,19,13,9], k = 3
  // 输出: 36
  vector<int> prices2 = {12, 16, 19, 19, 8, 1, 19, 13, 9};
  cout << solution.maximumProfit(prices2, 3) << endl;
  return 0;
}