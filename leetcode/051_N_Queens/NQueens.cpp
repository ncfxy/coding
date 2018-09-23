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
    vector<vector<string> > solveNQueens(int n)
    {
        vector<vector<string> > result;
        vector<int> nLineLocation(n);
        dfsSearch(n, 0, nLineLocation, result);
        return result;
    }

    void dfsSearch(int n, int currentLine, vector<int> &nLineLocation, vector<vector<string> > &result)
    {
        if(currentLine >= n){
            vector<string> oneSolution = generateQueen(nLineLocation);
            result.push_back(oneSolution);
            return;
        }
        for (int chooseLocation = 0; chooseLocation < n;chooseLocation++){
            if(judge(nLineLocation, currentLine, chooseLocation)){
                nLineLocation[currentLine] = chooseLocation;
                dfsSearch(n, currentLine + 1, nLineLocation, result);
            }
        }
    }

    vector<string> generateQueen(vector<int> &nLineLocation){
        vector<string> oneSolution;
        for (int i = 0; i < nLineLocation.size();i++){
            int qLoc = nLineLocation[i];
            string str = "";
            for (int j = 0; j < nLineLocation.size();j++){
                if(j == qLoc){
                    str += 'Q';
                }else {
                    str += '.';
                }
            }
            oneSolution.push_back(str);
        }
        return oneSolution;
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

    vector<vector<string> > result = so.solveNQueens(8);
    for (int i = 0; i < result.size();i++){
        for (int j = 0; j < result[i].size();j++){
            cout << result[i][j] << endl;
        }
        cout << endl
             << endl;
    }
        system("pause");
    return 0;
}
