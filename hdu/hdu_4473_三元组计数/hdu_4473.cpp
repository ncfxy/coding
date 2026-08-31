#include <iostream>
#include <cmath>

using namespace std;

using int64 = long long;

// floor(sqrt(x))
static inline int64 isqrt(int64 x) {
    int64 r = (int64)sqrtl((long double)x);

    while ((r + 1) * (r + 1) <= x) ++r;
    while (r * r > x) --r;

    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 n;
    int cas = 0;

    while (cin >> n) {
        int64 ans = 0;

        // a 是三个数中最小的那个
        // 必须有 a^3 <= n
        for (int64 a = 1; a * a * a <= n; ++a) {
            int64 m = n / a;

            // a <= b <= c
            // 存在 c >= b 的条件为：
            // a * b * b <= n
            // 即 b^2 <= floor(n / a)
            int64 limit = isqrt(m);

            for (int64 b = a; b <= limit; ++b) {
                // C = floor(n / (a*b))
                //   = floor(floor(n/a) / b)
                int64 C = m / b;

                if (a == b) {
                    // c = b: a = b = c，1 种
                    // c > b: a = b < c，每个 3 种排列
                    ans += 1 + 3 * (C - b);
                } else {
                    // c = b: a < b = c，3 种排列
                    // c > b: a < b < c，每个 6 种排列
                    ans += 3 + 6 * (C - b);
                }
            }
        }

        cout << "Case " << ++cas << ": " << ans << '\n';
    }

    return 0;
}