#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
  vector<vector<int> > combinationSum2(vector<int> &candidates, int target)
  {
      sort(candidates.begin(), candidates.end());
      return dfsCombinationSum2(candidates, target, candidates.size() - 1);
  }

  vector<vector<int> > dfsCombinationSum2(vector<int> &candidates, int target, int start){
      vector<vector<int> > result;
      if (target == 0){
          vector<int> ve;
          result.push_back(ve);
          return result;
      }
      if(start < 0){
          return result;
      }
      int eqCount = 1;
      for (int i = start - 1; i >= 0;i--){
          if(candidates[i] != candidates[start]){
              break;
          }
          eqCount++;
      }
      for (int i = 0; i <= eqCount && i * candidates[start] <= target;i++){
          vector<vector<int> > tmp = dfsCombinationSum2(candidates, target - i * candidates[start], start - eqCount);
          for (int j = 0; j < tmp.size();j++){
              for (int k = 0; k < i;k++){
                  tmp[j].push_back(candidates[start]);
              }
              result.push_back(tmp[j]);
          }
      }
      return result;
  }



};

int main()
{
    Solution so;
    int a[] = {10, 1, 2, 7, 6, 1, 5};
    vector<int> ca(a,a+7);
    vector<vector<int> > result = so.combinationSum2(ca, 8);
    for (int i = 0; i < result.size();i++){
        for (int j = 0; j < result[i].size();j++){
            cout << result[i][j];
        }
        cout << endl;
    }

    system("pause");
    return 0;
}

