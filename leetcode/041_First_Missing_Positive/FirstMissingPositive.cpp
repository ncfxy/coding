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
    int firstMissingPositive(vector<int> &nums)
    {
        int size = nums.size();
        vector<bool> buffer(size+1);
        for (int i = 0; i < size;i++){
            if(nums[i] <= size && nums[i] > 0){
                buffer[nums[i]] = true;
            }
        }
        int result = size + 1;
        for (int i = 1; i < size + 1;i++){
            if(!buffer[i]){
                result = i;
                break;
            }
        }
        return result;
    }
};

int main()
{
    Solution so;
    
    int a[3] = {1, 2, 0};
    vector<int> ve(a,a+3);
    cout << so.firstMissingPositive(ve) << endl;
    ;
    system("pause");
    return 0;
}
