#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

class Solution
{
public:
  vector<vector<int> > combinationSum(vector<int> &candidates, int target)
  {
      return dfsCombinationSum(candidates, target, candidates.size()-1);
  }

  vector<vector<int> > dfsCombinationSum(vector<int> &candidates, int target, int start){
      vector<vector<int> > result;
      if(target == 0){
          vector<int> a;
          result.push_back(a);
          return result;
      }
      if(start < 0){
          return result;
      }
      for (int i = 0; i * candidates[start] <= target;i++){
          vector<vector<int> > tmp = dfsCombinationSum(candidates, target - i * candidates[start], start - 1);
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
    vector<int> ca;
    ca.push_back(2);
    ca.push_back(3);
    ca.push_back(5);
    vector<vector<int> > result = so.combinationSum(ca, 8);
    for (int i = 0; i < result.size();i++){
        for (int j = 0; j < result[i].size();j++){
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
    system("pause");
    return 0;
}

