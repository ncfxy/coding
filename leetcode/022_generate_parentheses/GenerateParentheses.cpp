#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  vector<string> generateParenthesis(int n)
  {
      vector<string> result;
      dfs(result, "", 0, 0, n);
      return result;
  }

  void dfs(vector<string> &result, string tmp, int left, int right, int n){
    if(left < n){
        dfs(result, tmp + "(", left + 1, right, n);
    }
    if(left > right) {
        dfs(result, tmp + ")", left, right + 1, n);
    }
    if(left == n && right == n){
        result.push_back(tmp);
    }
    return;
  }
};

int main() {
    Solution so;
    vector<string> result = so.generateParenthesis(3);
    for (int i = 0; i < result.size();i++){
        cout << result[i] << endl;
    }
    system("pause");
    return 0;
}