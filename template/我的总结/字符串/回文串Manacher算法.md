# 回文串Manacher算法

## Manacher算法
```cpp
#include <bits/stdc++.h>
using namespace std;

/*
 * Manacher Algorithm
 *
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 *
 * p[i]:
 *   在处理后的字符串 t 中，
 *   以 i 为中心的最长回文串半径（不包括中心本身）
 *
 * 原字符串：
 *   s = "abba"
 *
 * 处理后：
 *   t = "^#a#b#b#a#$"
 *
 * 最长回文子串长度：
 *   max(p[i])
 */

struct Manacher {
    string s;       // 原字符串
    string t;       // 处理后的字符串
    vector<int> p;  // 回文半径

    Manacher(const string& str) {
        s = str;
        build();
        solve();
    }

    // 构造处理后的字符串
    // 例如：
    // abba -> ^#a#b#b#a#$
    void build() {
        t = "^";
        for (char c : s) {
            t += '#';
            t += c;
        }
        t += "#$";
    }

    void solve() {
        int n = t.size();
        p.assign(n, 0);

        int center = 0; // 当前最右回文串的中心
        int right = 0;  // 当前回文串最右边界

        for (int i = 1; i < n - 1; i++) {
            int mirror = 2 * center - i;

            // i 在当前回文串内部
            if (i < right) {
                p[i] = min(right - i, p[mirror]);
            }

            // 向左右扩展
            while (t[i + p[i] + 1] == t[i - p[i] - 1]) {
                p[i]++;
            }

            // 更新最右边界
            if (i + p[i] > right) {
                center = i;
                right = i + p[i];
            }
        }
    }

    // 返回最长回文子串长度
    int longestLength() {
        return *max_element(p.begin(), p.end());
    }

    // 返回最长回文子串
    string longestPalindrome() {
        int maxLen = 0;
        int centerIndex = 0;

        for (int i = 1; i < (int)p.size() - 1; i++) {
            if (p[i] > maxLen) {
                maxLen = p[i];
                centerIndex = i;
            }
        }

        // 转回原字符串的起点
        int start = (centerIndex - maxLen) / 2;

        return s.substr(start, maxLen);
    }
};

int main() {
    string s;
    cin >> s;

    Manacher manacher(s);

    cout << "最长回文子串长度: "
         << manacher.longestLength() << '\n';

    cout << "最长回文子串: "
         << manacher.longestPalindrome() << '\n';

    return 0;
}
```