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
    int totalNQueens(int n)
    {
        int result = 0;
        vector<int> nLineLocation(n);
        dfsSearch(n, 0, nLineLocation, result);
        return result;
    }

    void dfsSearch(int n, int currentLine, vector<int> &nLineLocation, int &result)
    {
        if(currentLine >= n){
            result++;
            return;
        }
        for (int chooseLocation = 0; chooseLocation < n;chooseLocation++){
            if(judge(nLineLocation, currentLine, chooseLocation)){
                nLineLocation[currentLine] = chooseLocation;
                dfsSearch(n, currentLine + 1, nLineLocation, result);
            }
        }
    }

    bool judge(vector<int> &nLineLocation, int currentLine, int chooseLocation){
        for (int i = 0; i < currentLine;i++){
            if(chooseLocation == nLineLocation[i]){
                return false;
            }
            if ((currentLine - i) == (chooseLocation - nLineLocation[i]) || (currentLine - i) == (nLineLocation[i] - chooseLocation)){
                return false;
            }
        }
        return true;
    }
};

int main()
{
    Solution so;

    cout << so.totalNQueens(4) << endl;
    cout << so.totalNQueens(8) << endl;

        system("pause");
    return 0;
}
