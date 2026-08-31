#include <iostream>
#include <vector>

using namespace std;

using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int64 n, k, u, v;
        cin >> n >> k >> u >> v;

        int64 L = k - 1;
        int64 R = n - k;

        // n = 1，没有任何马
        if (L + R == 0) {
            cout << 0 << '\n';
            continue;
        }

        // 向左一次、向右一次造成的价值变化
        int64 a = v - 2 * u;
        int64 b = u - 2 * v;

        // x 的最大可能值
        int64 X = (2 * L + R) / 3;

        vector<int64> cand;

        if (b >= 0) {
            int64 q = L / 2;

            cand.push_back(0);
            cand.push_back(min(X, q));

            if (q + 1 <= X)
                cand.push_back(q + 1);

            cand.push_back(X);
            cand.push_back(X - 1);
        } else {
            // 每一种奇偶性的 x 都是单调的
            cand.push_back(0);
            cand.push_back(1);

            cand.push_back(X);
            cand.push_back(X - 1);

            // 防止 X 或相邻端点恰好对应最终 (0,0)
            cand.push_back(X - 2);
            cand.push_back(X - 3);
        }

        int64 ans = LLONG_MAX;

        for (int64 x : cand) {
            if (x < 0 || x > X)
                continue;

            int64 low = max<int64>(0, 2 * x - L);
            int64 high = (R + x) / 2;

            if (low > high)
                continue;

            int64 y;

            if (b >= 0)
                y = low;
            else
                y = high;

            int64 finalL = L - 2 * x + y;
            int64 finalR = R + x - 2 * y;

            if (finalL < 0 || finalR < 0)
                continue;

            // 初始有马时，不可能把所有马全部吃光
            if (finalL == 0 && finalR == 0)
                continue;

            int64 value = u * finalL + v * finalR;
            ans = min(ans, value);
        }

        cout << ans << '\n';
    }

    return 0;
}