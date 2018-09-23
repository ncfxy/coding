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
    double myPow(double x, int n)
    {
        if(n < 0){
            return 1.0 / (myPow(x, -(n+1)) * x);
        }
        double result = 1;
        double tmpX = x;
        while(n){
            if(n & 1){
                result *= tmpX;
            }
            tmpX *= tmpX;
            n >>= 1;
        }
        return result;
    }
};

int main()
{
    Solution so;
    cout << so.myPow(2.0, 10) << endl;
    cout << so.myPow(2.1, 3) << endl;
    cout << so.myPow(2.0, -2) << endl;
    system("pause");
    return 0;
}
