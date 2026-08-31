
#include <iostream>
#include <vector>
using namespace std;

using int64 = long long;

static const int MOD = 998244353;

int64 qpow(int64 a, int64 e) {
    int64 r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    vector<int> ns(T);
    int mx = 1;

    for (int &n : ns) {
        cin >> n;
        mx = max(mx, n);
    }

    // 因为需要 inv[2*i]
    int lim = 2 * mx;

    vector<int64> inv(lim + 1);
    inv[1] = 1;

    // lim < MOD
    for (int i = 2; i <= lim; ++i) {
        inv[i] =
            MOD - (int64)(MOD / i) * inv[MOD % i] % MOD;
    }

    for (int n : ns) {
        if (n == 1) {
            cout << 0 << '\n';
            continue;
        }

        /*
         * SA[i] = sum_{j=i}^{n-1} a_j
         * SB[i] = sum_{j=i}^{n-1} b_j
         */
        vector<int64> SA(n + 1, 0);
        vector<int64> SB(n + 1, 0);

        int64 a1 = 0, b1 = 0;

        for (int i = n - 1; i >= 1; --i) {
            int64 ai, bi;
            int64 iv = inv[2 * i];

            if (2 * i >= n - 1) {
                // E_i = 1 + C / (2i)
                ai = iv;
                bi = 1;
            } else {
                /*
                 * a_i = (1 - SA[2i+1]) / (2i)
                 * b_i = 1 - SB[2i+1] / (2i)
                 */
                ai = (1 - SA[2 * i + 1] + MOD) % MOD;
                ai = ai * iv % MOD;

                bi =
                    (1 - SB[2 * i + 1] * iv % MOD + MOD)
                    % MOD;
            }

            SA[i] = (SA[i + 1] + ai) % MOD;
            SB[i] = (SB[i + 1] + bi) % MOD;

            if (i == 1) {
                a1 = ai;
                b1 = bi;
            }
        }

        /*
         * C = SA[1] * C + SB[1]
         *
         * C = SB[1] / (1 - SA[1])
         */
        int64 denominator =
            (1 - SA[1] + MOD) % MOD;

        int64 C =
            SB[1] * qpow(denominator, MOD - 2) % MOD;

        int64 ans =
            (a1 * C + b1) % MOD;

        cout << ans << '\n';
    }

    return 0;
}