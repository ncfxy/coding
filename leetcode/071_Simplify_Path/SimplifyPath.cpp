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
    string simplifyPath(string path)
    {
        path += "/";
        vector<string> pathBuffer;
        string tmp = "";
        for (int i = 0; i < path.length();i++){
            if(path[i] == '/'){
                if(tmp =="" || tmp == "."){

                }else if(tmp == ".." ){
                    if(pathBuffer.size() > 0){
                        pathBuffer.pop_back();
                    }
                }else {
                    pathBuffer.push_back(tmp);
                }
                tmp = "";
            }else{
                tmp += path[i];
            }
        }
        string res = "/";
        for (int i = 0; i < pathBuffer.size();i++){
            if(i == 0){
                res += pathBuffer[i];
            }else {
                res += "/" + pathBuffer[i];
            }
        }
        return res;
    }
};

int main()
{
    Solution so;

    cout << so.simplifyPath("/home/") << endl;
    cout << so.simplifyPath("/a/./b/../../c/") << endl;
    cout << so.simplifyPath("/a/../../b/../c//.//") << endl;
    cout << so.simplifyPath("/a//b////c/d//././/..") << endl;
    system("pause");
    return 0;
}
