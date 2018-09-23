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
    string addBinary(string a, string b)
    {
        if(a.length() < b.length()){
            return addBinary(b, a);
        }
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        int add = 0;
        for(int i = 0;i < a.length();i++){
            int tmpB = 0;
            if(i < b.length()){
                tmpB = b[i] - '0';
            }
            int tmpA = a[i] - '0';
            int res = tmpA + tmpB + add;
            add = res / 2;
            res %= 2;
            a[i] = (char)(res + '0');
        }
        if(add == 1){
            a += '1';
        }
        reverse(a.begin(), a.end());
        return a;
    }
};

int main()
{
    Solution so;

    cout << so.addBinary("11", "1") << endl;
    cout << so.addBinary("1010", "1011") << endl;
    system("pause");
    return 0;
}
