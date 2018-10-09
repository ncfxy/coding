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

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

class Solution
{
  public:
    int numTrees(int n)
    {
        vector<int> ve(n+1, 0);
        ve[0] = 0;
        ve[1] = 1;
        for (int i = 2; i <= n;i++){
            for (int j = 1; j <= i;j++){
                ve[i] += ve[max(1, j - 1)] * ve[max(1, i - j)];
            }
        }
        return ve[n];
    }
};

int main()
{
    Solution so;
    cout << so.numTrees(3) << endl;
    cout << so.numTrees(4) << endl;
    system("pause");
    return 0;
}
