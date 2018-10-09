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
    bool exist(vector<vector<char> > &board, string word)
    {
        vector<vector<bool> > mark;
        for (int i = 0; i < board.size();i++){
            vector<bool> bo;
            for (int j = 0; j < board[i].size();j++){
                bo.push_back(true);
            }
            mark.push_back(bo);
        }
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                if(board[i][j] == word[0]){
                    mark[i][j] = false;
                    if(dfs(board, mark, word, 1, i, j)){
                        return true;
                    }
                    mark[i][j] = true;
                }
            }
        }
        return false;
    }

    bool dfs(vector<vector<char> > &board, vector<vector<bool> > mark, string &word, int currentIndex, int currentX, int currentY){
        if(currentIndex == word.length()){
            return true;
        }
        int xChange[4] = {0, 0, 1, -1};
        int yChange[4] = {1, -1, 0, 0};
        for (int i = 0; i < 4;i++){
            int endX = currentX + xChange[i];
            int endY = currentY + yChange[i];
            if(endX < 0 || endX >= board.size() || endY < 0 && endY >= board[endX].size()){
                continue;
            }
            if(word[currentIndex] == board[endX][endY] && mark[endX][endY]){
                mark[endX][endY] = false;
                if(dfs(board, mark, word, currentIndex+1, endX, endY)){
                    return true;
                }
                mark[endX][endY] = true;
            }
        }
        return false;
    }
};

int main()
{
    Solution so;
    int char1[4] = {'A', 'B', 'C', 'E'};
    int char2[4] = {'S', 'F', 'C', 'S'};
    int char3[4] = {'A', 'D', 'E', 'E'};
    vector<vector<char> > input;
    vector<char> ve1(char1, char1 + 4);
    vector<char> ve2(char2, char2 + 4);
    vector<char> ve3(char3, char3 + 4);
    input.push_back(ve1);
    input.push_back(ve2);
    input.push_back(ve3);
    cout << so.exist(input, "ABCCED") << endl;
    cout << so.exist(input, "SEE") << endl;
    cout << so.exist(input, "ABCB") << endl;
    system("pause");
    return 0;
}
