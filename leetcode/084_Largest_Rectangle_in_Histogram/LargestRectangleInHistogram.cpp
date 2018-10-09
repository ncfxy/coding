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
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        int i = 0;
        int maxArea = 0;
        heights.push_back(0);
        while(i < heights.size()){
            if(st.empty() || heights[st.top()] <= heights[i]){
                st.push(i);
                i++;
            } else{
                int top = st.top();
                st.pop();
                maxArea = max(maxArea, heights[top] * (st.empty()?i:i-st.top()-1));
            }
        }
        heights.pop_back();
        return maxArea;
    }
};

int main()
{
    Solution so;
    int a[6] = {2, 1, 5, 6, 2, 3};
    vector<int> ve(a, a + 6);
    cout << so.largestRectangleArea(ve) << endl;

    system("pause");
    return 0;
}
