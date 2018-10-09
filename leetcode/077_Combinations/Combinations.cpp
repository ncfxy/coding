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
    vector<vector<int> > combine(int n, int k)
    {
        vector<vector<int> > result;
        vector<int> buffer;
        find(n, k, 0, 1, buffer, result);
        return result;
    }

    void find(int n, int k, int current, int chooseStart, vector<int> buffer, vector<vector<int> > & result){
        if(current == k){
            result.push_back(buffer);
            return;
        }
        for (int i = chooseStart; i <= n && n - i >= k - current-1;i++){
            buffer.push_back(i);
            find(n, k, current + 1, i + 1, buffer, result);
            buffer.pop_back();
        }
    }
};

int main()
{
    Solution so;
    vector<vector<int> > result = so.combine(4, 2);
    for (int i = 0; i < result.size();i++){
        for (int j = 0; j < result[i].size();j++){
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
        system("pause");
    return 0;
}
