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
    int uniquePaths(int m, int n)
    {
        vector<int> buffer(m, 1);
        for (int i = 1; i < n;i++){
            for (int j = 1; j < m;j++){
                buffer[j] = buffer[j - 1] + buffer[j];
            }
        }
        return buffer[m - 1];
    }
};

int main()
{
    Solution so;
    cout << so.uniquePaths(3, 2) << endl;
    cout << so.uniquePaths(7, 3) << endl;
    system("pause");
    return 0;
}
