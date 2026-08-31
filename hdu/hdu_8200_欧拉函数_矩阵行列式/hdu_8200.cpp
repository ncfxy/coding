#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

using int64 = long long;

static const int64 MOD = 998244353LL;

// ------------------------------------------------------------
// 快速幂
// ------------------------------------------------------------
int64 qpow(int64 a, int64 e) {
    int64 r = 1;

    while (e) {
        if (e & 1) {
            r = r * a % MOD;
        }
        a = a * a % MOD;
        e >>= 1;
    }

    return r;
}

// ------------------------------------------------------------
// 预处理 sqrt(1e7) 范围内的质数
// ------------------------------------------------------------
vector<int> getPrimes() {
    const int N = 3200;

    vector<bool> isPrime(N + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= N; ++i) {
        if (!isPrime[i]) continue;

        for (int j = i * i; j <= N; j += i) {
            isPrime[j] = false;
        }
    }

    vector<int> primes;

    for (int i = 2; i <= N; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

vector<int> primes;

// ------------------------------------------------------------
// Euler Phi
// ------------------------------------------------------------
int phi(int x) {
    if (x == 1) {
        return 1;
    }

    int n = x;
    int ans = x;

    for (int p : primes) {
        if (1LL * p * p > n) {
            break;
        }

        if (n % p == 0) {
            ans = ans / p * (p - 1);

            while (n % p == 0) {
                n /= p;
            }
        }
    }

    // 最后剩下一个大于 sqrt(original x) 的质因子
    if (n > 1) {
        ans = ans / n * (n - 1);
    }

    return ans;
}

// ------------------------------------------------------------
// 模 MOD 意义下的行列式
// O(n^3)
// ------------------------------------------------------------
int64 determinant(vector<vector<int64>> a) {
    int n = (int)a.size();

    int64 ans = 1;

    for (int col = 0; col < n; ++col) {

        // 寻找 pivot
        int pivot = -1;

        for (int row = col; row < n; ++row) {
            if (a[row][col] != 0) {
                pivot = row;
                break;
            }
        }

        // 当前列不存在 pivot，矩阵奇异
        if (pivot == -1) {
            return 0;
        }

        // 交换行
        if (pivot != col) {
            swap(a[pivot], a[col]);

            // determinant *= -1
            ans = (MOD - ans) % MOD;
        }

        int64 pivotValue = a[col][col];

        ans = ans * pivotValue % MOD;

        int64 invPivot = qpow(pivotValue, MOD - 2);

        // 消元
        for (int row = col + 1; row < n; ++row) {

            if (a[row][col] == 0) {
                continue;
            }

            int64 factor =
                a[row][col] * invPivot % MOD;

            for (int j = col; j < n; ++j) {
                a[row][j] =
                    (a[row][j]
                     - factor * a[col][j]) % MOD;

                if (a[row][j] < 0) {
                    a[row][j] += MOD;
                }
            }
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    primes = getPrimes();

    int T;
    cin >> T;

    while (T--) {

        int n;
        cin >> n;

        vector<int> a(n), b(n);

        for (int &x : a) {
            cin >> x;
        }

        for (int &x : b) {
            cin >> x;
        }

        // ----------------------------------------------------
        // 核心结论：
        // rank(C) <= 50
        // ----------------------------------------------------
        if (n > 50) {
            cout << 0 << '\n';
            continue;
        }

        vector<int> phiA(n), phiB(n);

        for (int i = 0; i < n; ++i) {
            phiA[i] = phi(a[i]);
            phiB[i] = phi(b[i]);
        }

        // 构造矩阵
        vector<vector<int64>> C(
            n,
            vector<int64>(n)
        );

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {

                int64 x = a[i] ^ b[j];

                int64 s =
                    (phiA[i] + phiB[j]) % MOD;

                C[i][j] = x % MOD * s % MOD;
            }
        }

        cout << determinant(C) << '\n';
    }

    return 0;
}