#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    // const string pat = "execute";
    const char pat[7] = {'e', 'x', 'e', 'c', 'u', 't', 'e'};

    while (T--) {
        string s;
        cin >> s;

        int n = (int)s.size();
        vector<int> pos;

        // 找出原字符串中所有 execute 的起点
        for (int i = 0; i + 7 <= n; ++i) {
            bool ok = true;
            for (int j = 0; j < 7; ++j) {
                if (s[i + j] != pat[j]) {
                    ok = false;
                    break;
                }
            }
            if (ok) pos.push_back(i);
        }

        // 将起点差为 6 的连续出现划分为一条链
        for (int l = 0; l < (int)pos.size(); ) {
            int r = l;
            while (r + 1 < (int)pos.size()
                   && pos[r + 1] == pos[r] + 6) {
                ++r;
            }

            int k = r - l + 1;   // 链中 execute 的数量
            int p = pos[l];

            if (k & 1) {
                // k 为奇数：b0, b2, b4, ...
                for (int j = 0; j < k; j += 2) {
                    s[p + 6 * j] = '1';
                }
            } else {
                // k 为偶数：b1, b3, b5, ...
                for (int j = 1; j < k; j += 2) {
                    s[p + 6 * j] = '1';
                }
            }

            l = r + 1;
        }

        cout << s << '\n';
    }

    return 0;
}