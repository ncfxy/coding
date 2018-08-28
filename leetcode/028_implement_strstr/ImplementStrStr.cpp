#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

class Solution
{
  public:
    int strStr(string haystack, string needle)
    {
        if(needle == ""){
            return 0;
        }
        for (int i = 0;;i++){
            for(int j = 0;;j++){
                if(j == needle.length()) return i;
                if(i + j >= haystack.length()) return -1;
                if(needle[j] != haystack[i+j])break;
            }
        }
        return -1;
    }
};

int main()
{
    Solution so;
    int result = so.strStr("abcc", "bcc");
    cout << result << endl;
    system("pause");
    return 0;
}
