#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while(T--) {
        string s;
        cin >> s;

        int ans = 1;

        // 当前 R/B 连续段
        int r = 0;     // 以 R 结尾的子序列数
        int b = 0;     // 以 B 结尾的子序列数
        int cnt = 0;   // 当前段最少需要的子序列数

        for(char c : s) {
            if (c == 'W') {
                ans = max(ans, cnt);

                // W 是重置点，开始新的 R/B段
                r = b = cnt = 0;
            } else if (c == 'R') {
                if (b > 0) {
                    // 接到一个 B 结尾的序列后
                    --b;
                    ++r;
                } else {
                    // 必须新开一轮
                    ++r;
                    ++cnt;
                }
            } else { // c == 'B'
                if (r > 0) {
                    // 接到一个 R 结尾的序列后
                    --r;
                    ++b;
                } else {
                    // 必须新开一轮
                    ++b;
                    ++cnt;
                }
            }
        }
        // 最后一段后面没有 W, 要单独统计
        ans = max(ans, cnt);

        cout << ans << '\n';
    }
    return 0;
}