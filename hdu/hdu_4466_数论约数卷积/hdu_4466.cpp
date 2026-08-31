
#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

const int MOD = 1000000007;
const int INV4 = 250000002;
const int INV6 = 166666668;
const int INV8 = 125000001;

inline int norm(long long x) {
    x %= MOD;
    if (x < 0) x += MOD;
    return (int)x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> query;

    int n, N = 0;
    while (cin >> n) {
        query.push_back(n);
        N = max(N, n);
    }

    if (query.empty())
        return 0;

    /*
     * phi:
     *   第一阶段保存 Euler phi
     *   第二阶段直接覆盖成 F(n)
     *
     * j2:
     *   只保存 J_2(n) mod MOD
     *
     * H:
     *   H(n) = mu * chi_4
     *   在本题范围内绝对值很小，int8_t 足够
     */
    vector<int> phi(N + 1, 0);
    vector<int> j2(N + 1, 0);
    vector<int8_t> H(N + 1, 0);

    vector<int> primes;
    primes.reserve(350000);

    phi[1] = 1;
    j2[1] = 1;
    H[1] = 1;

    // Euler 线性筛
    for (int i = 2; i <= N; ++i) {
        if (phi[i] == 0) {
            // i 是质数
            primes.push_back(i);

            phi[i] = i - 1;

            j2[i] =
                (1LL * i * i - 1) % MOD;

            if (i == 2) {
                H[i] = -1;
            } else if (i % 4 == 1) {
                H[i] = 0;
            } else {
                H[i] = -2;
            }
        }

        for (int p : primes) {
            long long v = 1LL * i * p;
            if (v > N)
                break;

            int x = (int)v;

            if (i % p == 0) {
                // phi(ip) = phi(i) * p
                phi[x] = phi[i] * p;

                // J2(ip) = J2(i) * p^2
                j2[x] =
                    1LL * j2[i] * p % MOD * p % MOD;

                /*
                 * H(p^k)
                 *
                 * p=2:
                 *   H(2)=-1
                 *   H(2^k)=0 (k>=2)
                 *
                 * p == 1 mod 4:
                 *   H(p^k)=0
                 *
                 * p == 3 mod 4:
                 *   H(p^k)=2*(-1)^k
                 */
                if (p == 2 || p % 4 == 1) {
                    H[x] = 0;
                } else {
                    H[x] = (int8_t)(-H[i]);
                }

                break;
            } else {
                // gcd(i,p)=1
                phi[x] = phi[i] * (p - 1);

                long long pp =
                    (1LL * p * p - 1) % MOD;

                j2[x] =
                    1LL * j2[i] * pp % MOD;

                H[x] =
                    (int8_t)((int)H[i] * (int)H[p]);
            }
        }
    }

    /*
     * Burnside:
     *
     * F(n) = (A(n) + 3B(n) + 2C(n)) / 6
     *
     * 注意：
     * j2[] 已经是模 MOD 的值，
     * 所以 A 的 /8 必须使用 INV8。
     *
     * 计算出的 F(n) 直接覆盖 phi[n]。
     */
    for (int x = 1; x <= N; ++x) {
        if (x < 3) {
            phi[x] = 0;
            continue;
        }

        long long ph = phi[x];

        long long A;
        long long B;
        long long C = (x == 3);

        if (x & 1) {
            /*
             * 奇数：
             *
             * A = J2(x) / 8
             */
            A = 1LL * j2[x] * INV8 % MOD;

            /*
             * B = (phi(x) - H(x)) / 4
             *
             * 这个值很小，可以直接做整数除法。
             */
            B = (ph - (int)H[x]) / 4;

        } else if (x % 4 == 0) {
            /*
             * A = (J2 - 6phi) / 8
             */
            long long tmp =
                norm((long long)j2[x] - 6LL * ph);

            A = tmp * INV8 % MOD;

            if (x == 4) {
                B = 0;
            } else {
                B = ph / 4;
            }

        } else {
            /*
             * x = 2 mod 4
             *
             * A = (J2 - 12phi) / 8
             */
            long long tmp =
                norm((long long)j2[x] - 12LL * ph);

            A = tmp * INV8 % MOD;

            /*
             * B = (phi(x) + H(x/2)) / 4
             */
            B =
                (ph + (int)H[x / 2]) / 4;
        }

        long long F =
            (A + 3LL * B + 2LL * C) % MOD;

        F = F * INV6 % MOD;

        // 覆盖 phi，后面 phi 就代表 F
        phi[x] = (int)F;
    }

    /*
     * 后面只需要 F(n)，
     * j2 / H / primes 可以全部释放。
     */
    vector<int>().swap(j2);
    vector<int8_t>().swap(H);
    vector<int>().swap(primes);

    /*
     * 此时内存主要只有：
     *
     * phi : 20MB
     * ans : 20MB
     *
     * 总计约 40MB。
     */
    vector<int> ans(N + 1, 0);

    /*
     * Ans(n)
     * =
     * sum_{d|n} F(d) * 2^(n/d-1)
     *
     * 令 n = k*d：
     *
     * ans[k*d] += F[d] * 2^(k-1)
     */
    long long pw = 1;

    for (int k = 1; k <= N; ++k) {
        long long coef = pw;

        int d = 1;

        for (int pos = k;
             pos <= N;
             pos += k, ++d) {

            ans[pos] =
                (ans[pos]
                 + 1LL * phi[d] * coef)
                % MOD;
        }

        pw = pw * 2 % MOD;
    }

    for (int tc = 0;
         tc < (int)query.size();
         ++tc) {

        cout << "Case "
             << tc + 1
             << ": "
             << ans[query[tc]]
             << '\n';
    }

    return 0;
}