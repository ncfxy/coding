#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Solution
{
  public:
    int longestValidParentheses(string s)
    {
        int res = 0, start = 0;
        stack<int> st;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '(')
            {
                st.push(i);
            }
            else
            {
                if (st.empty())
                {
                    start = i + 1;
                }
                else
                {
                    st.pop();
                    res = st.empty() ? max(res, i - start + 1) : max(res, i - st.top());
                }
            }
        }
        return res;
    }
};

int main()
{
    Solution so;
    int result;
    result = so.longestValidParentheses(")()");
    cout << result << endl;
    result = so.longestValidParentheses(")()())");
    cout << result << endl;
    result = so.longestValidParentheses(")(");
    cout << result << endl;
    result = so.longestValidParentheses("(()");
    cout << result << endl;
    result = so.longestValidParentheses("()(()");
    cout << result << endl;
    result = so.longestValidParentheses(")(((((()())()()))()(()))(");
    cout << result << endl;

    system("pause");
    return 0;
}
