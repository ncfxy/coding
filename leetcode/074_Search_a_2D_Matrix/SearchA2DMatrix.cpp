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
    bool searchMatrix(vector<vector<int> > &matrix, int target)
    {
        int outSize = matrix.size();
        int innerSize = outSize > 0 ? matrix[0].size() : 0;
        int right = outSize * innerSize - 1;
        int left = 0;
        while(left <= right){
            int mid = (left + right) >> 1;
            int row = mid / innerSize;
            int column = mid % innerSize;
            if(matrix[row][column] == target){
                return true;
            }else if(matrix[row][column] > target){
                right = mid - 1;
            }else {
                left = mid + 1;
            }
        }
        return false;
    }
};

int main()
{
    Solution so;
    int a[3][4] = {
        { 1, 3, 5, 7 },
        { 10, 11, 16, 20 },
        { 23, 30, 34, 50 }
    };
    vector<int> a1(a[0], a[0] + 4);
    vector<int> a2(a[1], a[1] + 4);
    vector<int> a3(a[2], a[2] + 4);
    vector<vector<int> > aVe;
    aVe.push_back(a1);
    aVe.push_back(a2);
    aVe.push_back(a3);
    cout << so.searchMatrix(aVe, 3) << endl;
    ;
    system("pause");
    return 0;
}
