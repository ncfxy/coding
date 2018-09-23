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
    map<int, bool> resultMap;
    int pLength;
    bool isMatch(string s, string p)
    {
        resultMap.clear();
        pLength = p.length()+1;
        return isMatchInner(s, p);
    }

    bool isMatchInner(string s, string p){
        int key = s.length() * pLength + p.length();
        map<int, bool>::iterator it = resultMap.find(key);
        if(it != resultMap.end()){
            return it->second;
        }
        bool result = false;
        if (s.empty() && p.empty())
        {
            result = true;
        }
        else if (!s.empty() && !p.empty())
        {
            if (s[0] == p[0] || p[0] == '?')
            {
                result = isMatchInner(s.substr(1), p.substr(1));
            }
            else if (p[0] == '*')
            {
                result = isMatchInner(s.substr(1), p) || isMatchInner(s, p.substr(1)) || isMatchInner(s.substr(1), p.substr(1));
            }
        }
        else if (s.empty() && !p.empty() && p[0] == '*')
        {
            result = isMatchInner(s, p.substr(1));
        }
        resultMap.insert(make_pair(key, result));
        return result;
    }
};

int main()
{
    Solution so;
    cout << so.isMatch("aa", "a") << endl;
    cout << so.isMatch("aa", "*") << endl;
    cout << so.isMatch("cb", "?a") << endl;
    cout << so.isMatch("adceb", "*a****b") << endl;
    cout << so.isMatch("acdcb", "a*c?b") << endl;
    cout << so.isMatch("aaabababaaabaababbbaaaabbbbbbabbbbabbbabbaabbababab", "*ab***ba**b*b*aaab*b") << endl;

    system("pause");
    return 0;
}
