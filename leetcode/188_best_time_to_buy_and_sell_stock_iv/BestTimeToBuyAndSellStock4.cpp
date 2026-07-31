#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int maxProfit(int k, vector<int> &prices) {
    if (prices.empty()) {
        return 0;
    }
    int n = prices.size();
    k = min(k, n / 2);
    vector<vector<int>> buy(k + 1, vector<int>(n, 0));
    vector<vector<int>> sell(k + 1, vector<int>(n, 0));
    buy[0][0] = -prices[0];
    sell[0][0] = 0;
    for (int i = 1; i <= k; i++) {
        buy[i][0] = -prices[0];
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= k; j++) {
            buy[j][i] = max(buy[j][i - 1], sell[j - 1][i - 1] - prices[i]);
            sell[j][i] = max(sell[j][i - 1], buy[j][i - 1] + prices[i]);
        }
    }
    return sell[k][n - 1];
  }
};
int main() {
  Solution solution;
  vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};
  cout << solution.maxProfit(2, prices) << endl;
  vector<int> prices2 = {1, 2, 3, 4, 5};
  cout << solution.maxProfit(2, prices2) << endl;
  vector<int> prices3 = {7, 6, 4, 3, 1};
  cout << solution.maxProfit(2, prices3) << endl;
  return 0;
}
