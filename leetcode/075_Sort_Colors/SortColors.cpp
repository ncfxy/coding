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
    void sortColors(vector<int> &nums)
    {
        int left = 0;
        int right = nums.size() - 1;
        int i = 0;
        while(i < nums.size() && i <= right){
            if(nums[i] == 0){
                if(i == left){
                    i++;
                }else{
                    swap(nums, i, left);
                }
                left++;
            }else if(nums[i] == 2){
                swap(nums, i, right);
                right--;
            }else{
                i++;
            }
        }
    }

    void swap(vector<int> &nums, int a, int b){
        int tmp = nums[a];
        nums[a] = nums[b];
        nums[b] = tmp;
    }
};

int main()
{
    Solution so;
    int a[6] = {2, 0, 2, 1, 1, 0};
    vector<int> ve(a, a + 6);
    so.sortColors(ve);
    for (int i = 0; i < ve.size();i++){
        cout << ve[i] << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}
