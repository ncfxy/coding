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
    int lengthOfLastWord(string s)
    {
        int i = s.length() - 1;
        int start=i, end=i;
        while (i >= 0 && s [i] == ' ')
        {
            end = start = i - 1;
            i--;
        }
        while(i >= 0 && s[i] != ' '){
            end = i-1;
            i--;
        }
        return start - end;
    }
};

int main()
{
    Solution so;
    cout << so.lengthOfLastWord("Hello World") << endl;
    cout << so.lengthOfLastWord("Hello World     ") << endl;
    cout << so.lengthOfLastWord("         ") << endl;
    cout << so.lengthOfLastWord("") << endl;
    system("pause");
    return 0;
}
