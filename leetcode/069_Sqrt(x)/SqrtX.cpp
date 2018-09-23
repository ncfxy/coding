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
    int mySqrt(int x)
    {
        long long maxCandidate = 0x0001ffff;
        long long minCandidate = 0;
        if(maxCandidate * maxCandidate < x){
            return maxCandidate;
        }
        while(minCandidate < maxCandidate-1){
            long long mid = (minCandidate + maxCandidate) >> 1;
            long long tmp = mid * mid;
            if(tmp == x){
                return mid;
            } else if(tmp > x){
                maxCandidate = mid;
            } else if(tmp < x){
                minCandidate = mid;
            }
        }
        return minCandidate;
    }
};

int main()
{
    Solution so;
    cout << so.mySqrt(4) << endl;
    cout << so.mySqrt(8) << endl;
    cout << so.mySqrt(2147395599) << endl;
    system("pause");
    return 0;
}
