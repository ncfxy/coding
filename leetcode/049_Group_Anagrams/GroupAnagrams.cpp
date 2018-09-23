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
    vector<vector<string> > groupAnagrams(vector<string> &strs)
    {
        map<string, vector<string> > bufferMap;
        vector<vector<string> > result;

        for (int i = 0; i < strs.size();i++){
            string s = strs[i];
            string s2 = sortStr(s);
            map<string, vector<string> >::iterator it = bufferMap.find(s2);
            if(it == bufferMap.end()){
                vector<string> ve;
                ve.push_back(strs[i]);
                bufferMap.insert(make_pair(s2, ve));
            }else{
                bufferMap[s2].push_back(strs[i]);
            }
        }
        map<string, vector<string> >::iterator it;
        for (it = bufferMap.begin(); it != bufferMap.end();it++){
            result.push_back(it->second);
        }
            return result;
    }

    string sortStr(string str){
        int length = str.length();
        for (int i = 0; i < length - 1;i++){
            for (int j = i + 1; j < length;j++){
                if(str[i] > str[j]){
                    char tmp = str[i];
                    str[i] = str[j];
                    str[j] = tmp;
                }
            }
        }
        return str;
    }
};

int main()
{
    Solution so;
    vector<string> ve;
    // ve.push_back("eat");
    // ve.push_back("tea");
    // ve.push_back("tan");
    // ve.push_back("ate");
    // ve.push_back("nat");
    // ve.push_back("bat");
    ve.push_back("");
    vector<vector<string> > result = so.groupAnagrams(ve);
    for (int i = 0; i < result.size();i++){
        for (int j = 0; j < result[i].size();j++){
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
        system("pause");
    return 0;
}
