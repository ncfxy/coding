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
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {
        int currentLocation = m + n - 1;
        m--;
        n--;
        while(m >= 0 && n >= 0){
            if(nums1[m] > nums2[n]){
                nums1[currentLocation--] = nums1[m--];
            }else{
                nums1[currentLocation--] = nums2[n--];
            }
        }
        while(n >= 0){
            nums1[currentLocation--] = nums2[n--];
        }
    }
};

int main()
{
    Solution so;
    int a[6] = {1, 2, 3, 0, 0, 0};
    int b[3] = {2, 5, 6};
    vector<int> ave(a, a + 6);
    vector<int> bve(b, b + 3);
    so.merge(ave, 3, bve, 3);
    for (int i = 0; i < 6;i++){
        cout << ave[i] << endl;
    }
        system("pause");
    return 0;
}
