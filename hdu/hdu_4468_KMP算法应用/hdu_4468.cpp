
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
    HDU 4468 - Spy

    fail[len]:
        模板长度为 len 的前缀，
        最长 proper border 的长度。
*/

int solve(const string& r) {
    int n = (int)r.size();

    // p 为动态维护的模板。
    vector<char> p(n + 1);

    // fail[len] = 长度为 len 的模板前缀的最长真前后缀长度
    vector<int> fail(n + 2, 0);

    p[0] = r[0];

    int m = 1;       // 当前模板长度
    int last = 1;    // 最近一次完整匹配结束后的下标
    int j = 0;       // 当前匹配的模板前缀长度

    for (int i = 1; i < n; ++i) {

        /*
            如果 j == m，说明前一个位置刚刚完整匹配了模板。
            现在继续匹配时，要像普通 KMP 一样退到 fail[m]。

            写成 j == m || ... 是为了避免访问 p[m] 越界。
        */
        while (j > 0 && (j == m || r[i] != p[j])) {
            j = fail[j];
        }

        if (j < m && r[i] == p[j]) {
            ++j;
        }

        /*
            j == 0：
            当前字符无法通过任何 KMP fail 跳转
            成为模板某个前缀的一部分。

            因此必须扩展模板。
        */
        if (j == 0) {

            // 把从上一次完整匹配之后到当前位置全部加入模板
            for (int k = last; k <= i; ++k) {
                char c = r[k];

                p[m] = c;

                // 动态计算 fail[m + 1]
                int t = fail[m];

                while (t > 0 && p[t] != c) {
                    t = fail[t];
                }

                if (p[t] == c) {
                    ++t;
                }

                fail[m + 1] = t;
                ++m;
            }

            // 新模板恰好完整匹配到 i
            j = m;
        }

        // 出现一次完整模板
        if (j == m) {
            last = i + 1;
        }
    }

    /*
        最后一段要求必须是完整的原串 s。

        p 在 [last-m, last-1] 已经完整出现，
        再把 r[last ... n-1] 加进去即可得到真正的 s。
    */
    return m + n - last;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string r;
    int tc = 0;

    while (cin >> r) {
        cout << "Case " << ++tc << ": "
             << solve(r) << '\n';
    }

    return 0;
}