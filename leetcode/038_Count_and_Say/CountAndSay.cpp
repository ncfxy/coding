#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

class Solution
{
public:
  string countAndSay(int n)
  {
      if(n == 0){
          return "";
      }
      string str = "1";
      for (int i = 1; i < n;i++){
          str = getNextStr(str);
          cout << str << endl;
      }
      return str;
  }

  string getNextStr(string str){
      string res = "";
      char ch='0';
      int count = 0;
      for (int i = 0; i < str.length();i++){
        if(ch != str[i]){
            if(count > 0){
                res += intToString(count);
                res += ch;
            }
            ch = str[i];
            count = 1;
        }else{
            count++;
        }
      }
      res += intToString(count);
      res += ch;
      return res;
  }

  string intToString(int x){
      string res = "";
      while(x){
          res = (char)('0' + x % 10) + res;
          x /= 10;
      }
      return res;
  }
};

int main()
{
    Solution so;
    so.countAndSay(10);

    system("pause");
    return 0;
}

