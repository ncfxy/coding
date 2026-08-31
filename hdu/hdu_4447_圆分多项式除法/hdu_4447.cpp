#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

using int64 = long long;

// a[i] 表示 x^i 的系数
using Poly = vector<int64>;

/*
 * 多项式整除
 *
 * 返回 a / b
 * 本题中一定能够整除。
 */
Poly dividePoly(Poly a, const Poly& b) {
    int da = (int)a.size() - 1;
    int db = (int)b.size() - 1;

    Poly q(da - db + 1, 0);

    // 从最高次开始消元
    for (int i = da; i >= db; --i) {
        if (a[i] == 0) continue;

        // 圆分多项式都是首一多项式，
        // 实际上 b[db] 恒等于 1
        int64 c = a[i] / b[db];

        int k = i - db;
        q[k] = c;

        for (int j = 0; j <= db; ++j) {
            a[k + j] -= c * b[j];
        }
    }

    while (q.size() > 1 && q.back() == 0) {
        q.pop_back();
    }

    return q;
}

/*
 * 按照题目规则比较两个不可约因子
 */
bool factorLess(const Poly& a, const Poly& b) {
    int da = (int)a.size() - 1;
    int db = (int)b.size() - 1;

    /*
     * 不同次数时：
     *
     * 小次数多项式在更高次数位置的系数可以看成 0。
     * 而圆分多项式最高项系数一定为 1，
     * 因此小次数一定排在前面。
     */
    if (da != db) {
        return da < db;
    }

    // 次数相同，从高次向低次逐项比较
    for (int i = da; i >= 0; --i) {
        if (a[i] == b[i]) continue;

        int64 aa = llabs(a[i]);
        int64 bb = llabs(b[i]);

        // 先比较绝对值
        if (aa != bb) {
            return aa < bb;
        }

        /*
         * 绝对值相同：
         * 负数排在正数前面。
         *
         * 例如 -2 < 2
         */
        return a[i] < b[i];
    }

    return false;
}

/*
 * 将一个多项式转成题目要求的字符串
 */
string polyToString(const Poly& p) {
    string ans;

    int d = (int)p.size() - 1;

    for (int i = d; i >= 0; --i) {
        int64 c = p[i];

        if (c == 0) continue;

        /*
         * 输出符号
         */
        if (ans.empty()) {
            if (c < 0) {
                ans += '-';
            }
        } else {
            ans += (c < 0 ? '-' : '+');
        }

        int64 v = llabs(c);

        /*
         * 输出系数
         *
         * 对非零次项：
         *   1x -> x
         *  -1x -> -x
         *
         * 常数项必须输出 1。
         */
        if (i == 0 || v != 1) {
            ans += to_string(v);
        }

        /*
         * 输出 x
         */
        if (i >= 1) {
            ans += 'x';

            if (i >= 2) {
                ans += '^';
                ans += to_string(i);
            }
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXN = 1100;

    /*
     * phi[n] = 第 n 个圆分多项式 Phi_n(x)
     */
    vector<Poly> phi(MAXN + 1);

    /*
     * 预处理所有 Phi_n。
     *
     * x^n - 1 = product_{d|n} Phi_d(x)
     *
     * 因而：
     *
     * Phi_n(x)
     * =
     * (x^n - 1)
     * /
     * product_{d|n,d<n} Phi_d(x)
     */
    for (int n = 1; n <= MAXN; ++n) {

        // cur = x^n - 1
        Poly cur(n + 1, 0);

        cur[0] = -1;
        cur[n] = 1;

        /*
         * 把所有真约数对应的 Phi_d 除掉
         */
        for (int d = 1; d < n; ++d) {
            if (n % d == 0) {
                cur = dividePoly(cur, phi[d]);
            }
        }

        phi[n] = move(cur);
    }

    int n;

    while (cin >> n && n != 0) {

        /*
         * x^n - 1 的不可约因子就是：
         *
         * Phi_d(x), d | n
         */
        vector<Poly> factors;

        for (int d = 1; d <= n; ++d) {
            if (n % d == 0) {
                factors.push_back(phi[d]);
            }
        }

        /*
         * 按照题目规定排序
         */
        sort(factors.begin(), factors.end(), factorLess);

        /*
         * n = 1 时只有 x-1，
         * 按题目要求不加括号。
         */
        if (factors.size() == 1) {
            cout << polyToString(factors[0]) << '\n';
            continue;
        }

        for (const Poly& p : factors) {
            cout << '(' << polyToString(p) << ')';
        }

        cout << '\n';
    }

    return 0;
}