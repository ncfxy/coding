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
    bool isNumber(string s)
    {
        s = trim(s);
        if(s.length() == 0){
            return false;
        }
        bool hasSign = false;
        bool hasBeginNumber = false;
        bool hasPoint = false;
        bool hasE = false;
        int length = s.length();
        for (int i = 0; i < length;i++){
            if(s[i] == ' '){
                if (hasSign || hasBeginNumber || hasPoint)
                {
                    return false;
                }
            } else if(s[i] == '+' || s[i] == '-'){
                if ((hasPoint || hasSign || hasBeginNumber) && (i > 0 && s[i - 1] != 'e') || i == s.length() - 1)
                {
                    return false;
                }
                hasSign = true;
            } else if(s[i] == '.'){
                if (hasE || hasPoint || (!hasBeginNumber && i == s.length() - 1))
                {
                    return false;
                }
                hasPoint = true;
            } else if(s[i] == 'e'){
                if(hasE || !hasBeginNumber || i == s.length()-1){
                    return false;
                }
                hasE = true;
            } else if(s[i] >= '0' && s[i] <= '9'){
                if(!hasBeginNumber){
                    hasBeginNumber = true;
                }
            }else{
                return false;
            }
            
        }
        return true;
    }

    string trim(string s)
    {
        while (s[0] == ' ')
        {
            s = s.substr(1);
        }
        while (s[s.length() - 1] == ' ')
        {
            s = s.substr(0, s.length() - 1);
        }
        return s;
    }
};

int main()
{
    Solution so;

    cout << so.isNumber("0") << endl;
    cout << so.isNumber(" 0.1 ") << endl;
    cout << so.isNumber("abc") << endl;
    cout << so.isNumber("1 a") << endl;
    cout << so.isNumber("2e10") << endl;
    cout << so.isNumber(" -90e3   ") << endl;
     cout << so.isNumber(" 1e") << endl;
     cout << so.isNumber("e3") << endl;
     cout << so.isNumber(" 6e-1") << endl;
     cout << so.isNumber(" 99e2.5 ") << endl;
     cout << so.isNumber("53.5e93") << endl;
     cout << so.isNumber(" --6 ") << endl;
     cout << so.isNumber("-+3") << endl;
     cout << so.isNumber("95a54e53") << endl;
     system("pause");
    return 0;
}
