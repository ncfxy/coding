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
    bool canJump(vector<int> &nums)
    {
        if(nums.size() == 1){
            return true;
        }
        int current = nums.size() - 1;
        int nearestZeroLocation = current;
        bool resolved = true;
        while(current >= 0){
            if(resolved && nums[current] == 0){
                resolved = false;
                nearestZeroLocation = current;
            }else if(!resolved){
                if (nums[current] > nearestZeroLocation - current || (nearestZeroLocation == nums.size()-1 && nums[current] == nearestZeroLocation - current))
                    resolved = true;
            }
            current--;
        }
        return resolved;
    }
};

int main()
{
    Solution so;
    int a[5] = {2, 3, 1, 1, 4};
    int b[5] = {3, 2, 1, 0, 4};
    vector<int> aVe(a, a + 5);
    vector<int> bVe(b, b + 5);
    cout << so.canJump(aVe) << endl;
    cout << so.canJump(bVe) << endl;
    vector<int> x;
    x.push_back(2);
    x.push_back(0);
    x.push_back(0);

    cout << so.canJump(x) << endl;

    system("pause");
    return 0;
}
