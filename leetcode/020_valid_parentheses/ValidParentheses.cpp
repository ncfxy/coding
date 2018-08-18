#include <iostream>
#include <string>
#include <cstdio>
#include <map>
#include <stack>
#include <cstdlib>

using namespace std;

class Solution{
public: 
    bool isValid(string s){
        stack<char> st;
        for (int i = 0; i < s.length();i++){
            char ch = getCorrespondingChar(s[i]);
            if(ch == '0'){
                st.push(s[i]);
            } else{
                if(!st.empty() && st.top() == ch){
                    st.pop();
                }else {
                    return false;
                }
            }
        }
        if(st.empty()){
            return true;
        }
        return false;
    }

    char getCorrespondingChar(char ch){
        switch(ch){
            case '}':
                return '{';
            case ']':
                return '[';
            case ')':
                return '(';
            default:
                return '0';
        }
    }
};

int main() {

    Solution so;
    cout << so.isValid("()") << endl;
    cout << so.isValid("()[]{}") << endl;
    cout << so.isValid("(]") << endl;
    cout << so.isValid("]") << endl;
    system("pause");
    return 0;
}