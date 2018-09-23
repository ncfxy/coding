#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
  string multiply(string num1, string num2)
  {
      string result = "0";
      for (int i = 0; i < num1.length();i++){
          string tmp = multiplySingle(num2, num1[num1.length()-1 - i]);
          for (int j = 0; j < i;j++){
              tmp = tmp + "0";
          }
          result = add(result, tmp);
      }
      while(result.length() > 1 && result[0] == '0'){
          result = result.substr(1);
      }
      return result;
  }

  string multiplySingle(string num, char ch){
      string result = "";
      int add = 0;
      for (int i = 0; i < num.length();i++){
          int tmp = (num[num.length()-1 - i] - '0') * (ch - '0') + add;
          int remainder = tmp % 10;
          add = tmp / 10;
          result = (char)(remainder + '0') + result;
      }
      if (add > 0)
      {
          result = (char)(add + '0') + result;
      }
      return result;
  }

  string add(string num1, string num2){
      if(num1.length() < num2.length()){
          return add(num2, num1);
      }
      string result = "";
      int add = 0;
      int i;
      for (i = 0; i < num1.length();i++){
          int tmp = (num1[num1.length()-1 - i] - '0') + add;
          if (i < num2.length()){
              tmp += (num2[num2.length()-1 - i] - '0');
          }
          int remainder = tmp % 10;
          add = tmp / 10;
          result = (char)(remainder+'0') + result;
      }
      if (add > 0)
      {
          result = '1' + result;
      }
      return result;
  }
};

int main()
{
    Solution so;
    cout << so.multiply("123", "456") << endl;
    cout << so.multiply("123", "0") << endl;

    system("pause");
    return 0;
}

