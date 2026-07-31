#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int maxProfit(vector<int> &prices) {
    int n = prices.size();
    int buy1 = -prices[0], sell1 = 0;
    int buy2 = -prices[0], sell2 = 0;
    for (int i = 1; i < n; ++i) {
      buy1 = max(buy1, -prices[i]);
      sell1 = max(sell1, buy1 + prices[i]);
      buy2 = max(buy2, sell1 - prices[i]);
      sell2 = max(sell2, buy2 + prices[i]);
    }
    return sell2;
  }
};

int main() {
  Solution solution;

  //   输入：prices = [3,3,5,0,0,3,1,4]
  // 输出：6
  vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};
  cout << solution.maxProfit(prices) << endl;
  //   输入：prices = [1,2,3,4,5]
  // 输出：4
  vector<int> prices2 = {1, 2, 3, 4, 5};
  cout << solution.maxProfit(prices2) << endl;
  //   输入：prices = [7,6,4,3,1]
  // 输出：0
  vector<int> prices3 = {7, 6, 4, 3, 1};
  cout << solution.maxProfit(prices3) << endl;
  return 0;
}