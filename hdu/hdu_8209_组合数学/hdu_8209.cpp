#include <iostream>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e7 + 5;
long long fact[MAXN], invfact[MAXN];

// 快速幂：计算 a^b % MOD
long long qpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void init(int n) {
    // 1. 求阶乘
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i % MOD;

    // 2. 求最大的阶乘的逆元 (费马小定理)
    invfact[n] = qpow(fact[n], MOD - 2);

    // 3. 递推求出所有阶乘的逆元
    for (int i = n; i >= 1; i--) invfact[i-1] = invfact[i] * i % MOD;
}

// 计算组合数 C(n, m)
long long C(int n, int m) {
    if (m < 0 || m > n) return 0;
    return fact[n] * invfact[m] % MOD * invfact[n-m] % MOD;
}


int main() {
    init(1e7);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        // 如果n为奇数，输出2^(n-1)的逆元
        if (n % 2 == 1) {
            cout << qpow(qpow(2, n-1), MOD - 2) << endl;
        } else {
            // 如果n为偶数，输出(2 + c(n, n/2)) / 2^n的逆元
            cout << (2 + C(n, n/2)) * qpow(qpow(2, n), MOD - 2) % MOD << endl;
        }
    }
    return 0;
}