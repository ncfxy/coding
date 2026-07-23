#include <iostream>
#include <vector>
using namespace std;

using int64 = long long;

vector<int> getPrimes() {
    const int LIM = 31623; // sqrt(1e9)
    vector<bool> isPrime(LIM + 1, true);
    vector<int> primes;

    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= LIM; ++i) {
        if (!isPrime[i]) continue;
        primes.push_back(i);
        if (1LL * i * i <= LIM) {
            for (int j = i * i; j <= LIM; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return primes;
}

int64 phi(int64 x, const vector<int>& primes) {
    int64 result = x;
    int64 remain = x;

    for (int prime : primes) {
        if (1LL * prime * prime > remain) break;
        if (remain % prime == 0) {
            result = result / prime * (prime - 1);
            while (remain % prime == 0) {
                remain /= prime;
            }
        }
    }

    if (remain > 1) {
        result = result / remain * (remain - 1);
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> primes = getPrimes();

    int T;
    cin >> T;

    while (T--) {
        int64 p, k;
        cin >> p >> k;

        int64 n = p - 1;

        if (n % k != 0) {
            cout << 0 << " " << 1 << '\n';
            continue;
        }

        int64 d = n / k;
        int64 count = phi(d, primes);

        // 仅 d=2 时乘积为 -1 mod p
        int64 product = (d == 2 ? p - 1 : 1);

        cout << count << " " << product << '\n';
    }

    return 0;
}