
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

/*
    计算：

    sum_{j=0}^n
        (n-j) * C(n+j, j) * a^(n+1) * b^j

    其中 a + b = 1.
*/
long double calc(int n, long double a, long double b) {
    // 这种盒子永远不会被选择，所以不可能先空
    if (a == 0.0L) {
        return 0.0L;
    }

    // b = 0 => a = 1
    // 另一个盒子从未被选过，因此剩 n 颗
    if (b == 0.0L) {
        return (long double)n;
    }

    /*
        T_j = C(n+j, j) * a^(n+1) * b^j

        峰值大约位于：
            j = floor(n*b/a)

        但只考虑 j <= n.
    */
    long double pos = (long double)n * b / a;

    int m;
    if (pos >= n) {
        m = n;
    } else {
        m = (int)floorl(pos);
    }

    /*
        使用 log 计算峰值位置的概率：

        log(T_m)
        = log C(n+m,m)
          + (n+1)log(a)
          + m log(b)
    */
    long double logT =
        lgammal((long double)n + m + 1.0L)
        - lgammal((long double)n + 1.0L)
        - lgammal((long double)m + 1.0L)
        + ((long double)n + 1.0L) * logl(a)
        + (long double)m * logl(b);

    long double tm = expl(logT);

    long double ans =
        (long double)(n - m) * tm;

    /*
        向左递推：

        T_{j-1}
        = T_j * j / ((n+j)*b)
    */
    long double t = tm;

    for (int j = m; j >= 1; --j) {
        t *= (long double)j
             / ((long double)(n + j) * b);

        int k = j - 1;

        ans += (long double)(n - k) * t;
    }

    /*
        向右递推：

        T_{j+1}
        = T_j * (n+j+1)/(j+1) * b
    */
    t = tm;

    for (int j = m; j < n; ++j) {
        t *= (long double)(n + j + 1)
             / (long double)(j + 1)
             * b;

        int k = j + 1;

        ans += (long double)(n - k) * t;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long double p;

    int tc = 0;

    while (cin >> n >> p) {
        ++tc;

        long double q = 1.0L - p;

        long double ans =
            calc(n, p, q)
            + calc(n, q, p);

        cout << "Case " << tc << ": "
             << fixed << setprecision(6)
             << (double)ans << '\n';
    }

    return 0;
}