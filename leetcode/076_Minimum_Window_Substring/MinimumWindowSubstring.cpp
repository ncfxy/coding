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
    string minWindow(string s, string t)
    {
        map<char, int> myMap;
        for (int i = 0; i < t.length();i++){
            map<char, int>::iterator it = myMap.find(t[i]);
            if(it != myMap.end()){
                it->second++;
            }else{
                myMap.insert(make_pair(t[i], 1));
            }
        }
        int left = 0, right = 0;
        int lack = t.length();
        int minLength = s.size()+1;
        string targetString = "";
        while(left <= s.length() && right <= s.length()){
            if(lack > 0){
                if(right == s.length())
                    break;
                map<char, int>::iterator it = myMap.find(s[right]);
                if(it != myMap.end()){
                    if(it->second > 0){
                        lack--;
                    }
                    it->second--;
                }
                right++;
            }else{
                if(right - left < minLength){
                    minLength = right - left;
                    targetString = s.substr(left, right - left);
                }
                map<char, int>::iterator it = myMap.find(s[left]);
                if(it != myMap.end()){
                    if(it->second >= 0){
                        lack++;
                    }
                    it->second++;
                }
                left++;
            }
        }
        return targetString;
    }
};

int main()
{
    Solution so;
    cout << so.minWindow("ADOBECODEBANC", "ABC") << endl;
    cout << so.minWindow("a", "a") << endl;
    cout << so.minWindow("a", "aa") << endl;
    system("pause");
    return 0;
}
