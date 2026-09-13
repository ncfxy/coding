#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {
        if (s.empty()) return "";
        
        int n = s.size();
        string rev = s;
        reverse(rev.begin(), rev.end());
        
        // 构造辅助字符串 t = s + "#" + rev
        string t = s + "#" + rev;
        
        // 计算前缀函数 pi
        vector<int> pi(t.size(), 0);
        for (int i = 1; i < t.size(); ++i) {
            int j = pi[i - 1];
            while (j > 0 && t[i] != t[j]) {
                j = pi[j - 1];
            }
            if (t[i] == t[j]) {
                ++j;
            }
            pi[i] = j;
        }
        
        // pi 的最后一个值就是 s 的最长回文前缀长度
        int l = pi.back();
        
        // 剩余后缀的反转就是 rev 的前 n - l 个字符
        return rev.substr(0, n - l) + s;
    }
};

// 测试代码
int main() {
    Solution sol;
    string s1 = "aacecaaa";
    string s2 = "abcd";
    cout << sol.shortestPalindrome(s1) << endl; // 输出 aaacecaaa
    cout << sol.shortestPalindrome(s2) << endl; // 输出 dcbabcd
    return 0;
}