#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  int maxProfit(vector<int> &prices) {
    if(prices.size() < 2) return 0;
    int ans = 0;
    for(int i = 1; i < prices.size(); i++) {
      if(prices[i] > prices[i-1]) {
        ans += prices[i] - prices[i-1];
      }
    }
    return ans;
  }
};

int main() {
    Solution solution;
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << solution.maxProfit(prices) << endl;
    return 0;
}