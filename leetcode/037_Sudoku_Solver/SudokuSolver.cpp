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
  void solveSudoku(vector<vector<char> > &board)
  {
      bool row[9][9];
      bool column[9][9];
      bool box[9][9];
      for (int i = 0; i < 9;i++){
          for (int j = 0; j < 9;j++){
              row[i][j] = true;
              column[i][j] = true;
              box[i][j] = true;
          }
      }
      for (int i = 0; i < 9; i++)
      {
          for (int j = 0; j < 9; j++)
          {
              if(board[i][j] != '.'){
                  int cc = board[i][j] - '1';
                  row[i][cc] = false;
                  column[j][cc] = false;
                  int boxLocation = i / 3 * 3 + j / 3;
                  box[boxLocation][cc] = false;
              }
          }
      }
      dfs(board, 0, 0, row, column, box);
  }


  vector<int> toNext(int rowIndex, int columnIndex){
      vector<int> newLocation;
      newLocation.push_back(rowIndex);
      newLocation.push_back(columnIndex);
      newLocation[1]++;
      if (newLocation[1] >= 9)
      {
          newLocation[0]++;
          newLocation[1] = 0;
      }
      return newLocation;
  }

  bool dfs(vector<vector<char> > &board, int rowIndex, int columnIndex, bool row[][9], bool column[][9], bool box[][9]){
      if(rowIndex >= 9 || columnIndex >= 9){
          return true;
      }
      vector<int> newLocation = toNext(rowIndex, columnIndex);
      if(board[rowIndex][columnIndex] != '.'){
          return dfs(board, newLocation[0], newLocation[1], row, column, box);
      }else {
          int boxLocation = rowIndex / 3 * 3 + columnIndex / 3;
          for (int i = 0; i < 9;i++){
              if(row[rowIndex][i] && column[columnIndex][i] && box[boxLocation][i]){
                  row[rowIndex][i] = false;
                  column[columnIndex][i] = false;
                  box[boxLocation][i] = false;
                  board[rowIndex][columnIndex] = (char)(i + '1');
                  bool result = dfs(board, newLocation[0], newLocation[1], row, column, box);
                  if(result){
                      return true;
                  }else {
                      board[rowIndex][columnIndex] = '.';
                      row[rowIndex][i] = true;
                      column[columnIndex][i] = true;
                      box[boxLocation][i] = true;
                  }
                  
              }
          }
          if(board[rowIndex][columnIndex] == '.'){
              return false;
          }
      }
  }
};

int main()
{
    Solution so;
    char a[9][9] = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    vector<vector<char> > ve;
    for (int i = 0; i < 9;i++){
        vector<char> tmp;
        for (int j = 0; j < 9;j++){
            tmp.push_back(a[i][j]);
        }
        ve.push_back(tmp);
    }
    so.solveSudoku(ve);
    for (int i = 0; i < ve.size();i++){
        for (int j = 0; j < ve[i].size();j++){
            cout << ve[i][j] << ' ';
        }
        cout << endl;
    }

    system("pause");
    return 0;
}

