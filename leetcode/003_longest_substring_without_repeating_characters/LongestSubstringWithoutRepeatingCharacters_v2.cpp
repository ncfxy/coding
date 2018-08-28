#include <cstdio>
#include <cstdlib>
#include <iostream>

// 使用移动窗口的解法

using namespace std;

class Solution
{

public:
    int lengthOfLongestSubstring(string s)
    {
        if(s.length() == 0){
            return 0;
        }
        bool hash[257];
        for (int i = 0; i < 257;i++){
            hash[i] = false;
        }
        int left = 0, right = 0;
        int max = 0;
        while(right < s.length()){
            int temp = (int)(s[right]);
            if(hash[temp]){
                if(max < right - left){
                    max = right - left;
                }
                while(s[left] != s[right]){
                    int temp2 = (int)(s[left]);
                    hash[temp2] = false;
                    left++;
                }
                left++;
            }else {
                hash[temp] = true;
            }
            right++;
        }
        if(max < right - left){
            max = right - left;
        }
        return max;
    }
};

int main()
{
    Solution so;
    int l = so.lengthOfLongestSubstring("abcabcbb");
    cout << l << endl;
    l = so.lengthOfLongestSubstring(" ");
    cout << l << endl;
    system("pause");
    return 0;
}