#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Solution
{
  public:
    vector<string> letterCombinations(string digits)
    {
        map<int, string> phoneMap;
        make_pair(2, "abc");
        phoneMap.insert(make_pair(2, "abc"));
        phoneMap.insert(make_pair(3, "def"));
        phoneMap.insert(make_pair(4, "ghi"));
        phoneMap.insert(make_pair(5, "jkl"));
        phoneMap.insert(make_pair(6, "mno"));
        phoneMap.insert(make_pair(7, "pqrs"));
        phoneMap.insert(make_pair(8, "tuv"));
        phoneMap.insert(make_pair(9, "wxyz"));
        vector<string> result;
        dfs(0, result, phoneMap, digits, "");
        return result;
    }

    void dfs(int index, vector<string> &result, map<int, string> &phoneMap, string &digits, string buffer){
        if(index > digits.length()-1){
            return;
        }
        string relatedStr = phoneMap[digits[index] - '0'];
        for (int i = 0; i < relatedStr.length(); i++)
        {
            if (index == digits.length()-1)
            {
                result.push_back(buffer + relatedStr[i]);
            }
            dfs(index + 1, result, phoneMap, digits, buffer + relatedStr[i]);
        }
    }
};

int main(){
    Solution so;
    vector<string> result = so.letterCombinations("23");
    for (int i = 0; i < result.size();i++){
        cout << result[i] << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}