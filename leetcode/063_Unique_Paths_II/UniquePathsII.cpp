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
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid)
    {
        if (obstacleGrid.size() == 0)
        {
            return 0;
        }
        int outSize = obstacleGrid.size();
        int size = obstacleGrid[0].size();
        if (obstacleGrid[outSize - 1][size - 1] == 1 || obstacleGrid[0][0] == 1)
        {
            return 0;
        }
        vector<int> buffer(size, 0);
        buffer[0] = 1;
        for (int i = 0; i < outSize; i++)
        {
            if (obstacleGrid[i][0] == 1)
            {
                buffer[0] = 0;
            }
            for (int j = 1; j < size; j++)
            {
                if (obstacleGrid[i][j] == 1)
                {
                    buffer[j] = 0;
                }
                else
                {
                    buffer[j] = buffer[j - 1] + buffer[j];
                }
            }
        }

        return buffer[size - 1];
    }
};

int main()
{
    Solution so;
    vector<vector<int> > grid;
    int g[3][3] = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}};
    vector<int> a(g[0], g[0] + 3);
    vector<int> b(g[1], g[1] + 3);
    vector<int> c(g[2], g[2] + 3);
    grid.push_back(a);
    grid.push_back(b);
    grid.push_back(c);
    cout << so.uniquePathsWithObstacles(grid) << endl;
    system("pause");
    return 0;
}
