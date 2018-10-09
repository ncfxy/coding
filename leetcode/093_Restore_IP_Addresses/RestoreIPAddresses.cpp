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
    vector<string> restoreIpAddresses(string s)
    {
        vector<string> result;
        string buffer = "";
        dfs(s, 0, 0, buffer, result);
        return result;
    }

    void dfs(string s, int currentIndex, int depth, string buffer, vector<string> &result){
        if(depth == 3){
            string area = s.substr(currentIndex);
            if(judgeArea(area)){
                result.push_back(buffer + area);
            }
            return;
        }
        for (int i = 1; i <= 3 && currentIndex + i < s.length();i++){
            string area = s.substr(currentIndex, i);
            if(judgeArea(area)){
                dfs(s, currentIndex + i, depth + 1, buffer + area + ".", result);
            }
        }
    }

    bool judgeArea(string area){
        if(area[0] == '0' && area.length() > 1){
            return false;
        }
        int result = 0;
        for (int i = 0; i < area.length();i++){
            result = result * 10 + (area[i] - '0');
        }
        if(result >= 0 && result <= 255){
            return true;
        }
        return false;
    }
};

int main()
{
    Solution so;

    vector<string> result = so.restoreIpAddresses("0000");
    result = so.restoreIpAddresses("25525511135");
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << endl;
    }

        system("pause");
    return 0;
}
