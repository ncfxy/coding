#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    const int n = (int)s.size();

    vector<int64> ans(n, 0);

    /*
     * inverted = false:
     *   使用全局转换得到的括号串 t
     *
     * inverted = true:
     *   使用左右括号交换后的 t
     *
     * needParity:
     *   0 -> 左端点为 0-based 偶数，即原来的 1-based 奇数
     *   1 -> 左端点为 0-based 奇数，即原来的 1-based 偶数
     */
    auto solve = [&](bool inverted, int needParity) {
        // 判断位置 i 在当前括号串中是不是左括号
        auto isOpen = [&](int i) -> bool {
            bool op;

            // 全局转换：
            // 1-based 奇数位置：" 为 (
            // 1-based 偶数位置：' 为 (
            if ((i & 1) == 0) {
                op = (s[i] == '"');
            } else {
                op = (s[i] == '\'');
            }

            if (inverted) op = !op;
            return op;
        };

        /*
         * group id:
         *
         * 如果一个节点有父左括号 p：
         *     group = p, 范围 [0, n-1]
         *
         * 如果是最外层：
         *     group = n + rootSegment
         *
         * 最多不超过 2n。
         */
        const int G = 2 * n + 5;

        vector<int> match(n, -1);
        vector<int> remain(G, 0);

        vector<int> stk;
        stk.reserve(n);

        /*
         * 第一遍：
         * 1. 完成括号匹配
         * 2. 统计每个兄弟组中匹配节点总数
         */
        int rootSegment = 0;

        for (int i = 0; i < n; ++i) {
            if (isOpen(i)) {
                stk.push_back(i);
            } else {
                if (stk.empty()) {
                    // 最外层未匹配右括号。
                    // 后面的节点不能和前面的根节点拼成合法括号串。
                    ++rootSegment;
                } else {
                    int L = stk.back();
                    stk.pop_back();

                    match[L] = i;

                    int group;
                    if (stk.empty()) {
                        group = n + rootSegment;
                    } else {
                        group = stk.back();
                    }

                    ++remain[group];
                }
            }
        }

        /*
         * 第二遍：
         *
         * seen[group]：
         * 当前兄弟组前面（含当前）有多少个节点
         * 可以作为满足奇偶条件的合法起点。
         */
        vector<int> seen(G, 0);
        vector<int64> diff(n + 1, 0);

        stk.clear();
        rootSegment = 0;

        for (int i = 0; i < n; ++i) {
            if (isOpen(i)) {
                int group;
                if (stk.empty()) {
                    group = n + rootSegment;
                } else {
                    group = stk.back();
                }

                // 只有匹配成功的左括号才是一个有效节点
                if (match[i] != -1) {
                    if ((i & 1) == needParity) {
                        ++seen[group];
                    }

                    /*
                     * 当前节点是兄弟组中的第 x 个：
                     *
                     * seen[group] = E_x
                     * remain[group] = m-x+1
                     */
                    int64 weight =
                        1LL * seen[group] * remain[group];

                    --remain[group];

                    // 当前节点整个区间都被这些合法子串覆盖
                    diff[i] += weight;
                    diff[match[i] + 1] -= weight;
                }

                stk.push_back(i);
            } else {
                if (stk.empty()) {
                    ++rootSegment;
                } else {
                    stk.pop_back();
                }
            }
        }

        int64 cur = 0;
        for (int i = 0; i < n; ++i) {
            cur += diff[i];
            ans[i] += cur;
        }
    };

    /*
     * l 为 1-based 奇数：
     * 原括号串是合法括号串。
     */
    solve(false, 0);

    /*
     * l 为 1-based 偶数：
     * 左右括号交换之后是合法括号串。
     */
    solve(true, 1);

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}