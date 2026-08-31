
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;

    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;

        vector<double> boys(n), girls(m);

        for (double &x : boys) cin >> x;
        for (double &x : girls) cin >> x;

        // a 始终表示人数较少的一方
        vector<double> a, b;

        if (n <= m) {
            a = boys;
            b = girls;
        } else {
            a = girls;
            b = boys;
            swap(n, m);
        }

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        // 现在 n <= m
        int d = m - n;

        vector<double> pre(d + 1, 0.0);
        vector<double> cur(d + 1);

        for (int i = 1; i <= n; ++i) {
            // 不跳过任何人
            cur[0] = pre[0] + fabs(a[i - 1] - b[i - 1]);

            for (int j = 1; j <= d; ++j) {
                // 方案1：
                // a[i-1] 与 b[i+j-1] 匹配
                double match =
                    pre[j] + fabs(a[i - 1] - b[i + j - 1]);

                // 方案2：
                // 跳过 b[i+j-1]
                double skip = cur[j - 1];

                cur[j] = min(match, skip);
            }

            swap(pre, cur);
        }

        cout << fixed << setprecision(6) << pre[d] << '\n';
    }

    return 0;
}