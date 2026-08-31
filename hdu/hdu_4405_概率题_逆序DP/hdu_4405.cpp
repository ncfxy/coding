#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;

    while(cin >> N >> M) {
        if(N == 0 && M == 0) break;

        // fly[i] = j 表示 i -> j 有航线
        // -1 表示没有航线
        vector<int> fly(N + 1, -1);

        for (int i = 0; i < M; ++i) {
            int x, y;
            cin >> x >> y;
            fly[x] = y;
        }

        vector<double> dp(N + 7, 0.0);

        // dp[N] 以及 N 之后的位置都视为 0
        for (int i = N - 1; i >= 0; --i) {
            if (fly[i] != -1) {
                // 乘坐航线不需要掷骰子
                dp[i] = dp[fly[i]];
            } else {
                // 必须掷一次骰子
                dp[i] = 1.0;

                for (int k = 1; k <= 6; ++k) {
                    if (i + k < N) {
                        dp[i] += dp[i + k] / 6.0;
                    }
                    // i + k >= N 时直接结束，后续期望为 0
                }
            }
        }
        cout << fixed << setprecision(4) << dp[0] << '\n';
    }
    return 0;
}