#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

using int64 = long long;

static const int64 MOD = 1000000007LL;

struct Special {
    int64 pos;
    int t;
    vector<int64> c;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc = 0;

    int64 n;
    int m, q;

    while (cin >> n >> m >> q) {
        ++tc;

        // f[1..m]
        vector<int64> init(m + 1);
        for (int i = 1; i <= m; ++i) {
            cin >> init[i];
            init[i] %= MOD;
        }

        // Ordinary recurrence
        int t;
        cin >> t;

        vector<int64> ordinary(t);
        for (int i = 0; i < t; ++i) {
            cin >> ordinary[i];
            ordinary[i] %= MOD;
        }

        // Special recurrence positions
        vector<Special> sp(q);

        for (int i = 0; i < q; ++i) {
            cin >> sp[i].pos >> sp[i].t;

            sp[i].c.resize(sp[i].t);

            for (int j = 0; j < sp[i].t; ++j) {
                cin >> sp[i].c[j];
                sp[i].c[j] %= MOD;
            }
        }

        sort(sp.begin(), sp.end(),
             [](const Special& a, const Special& b) {
                 return a.pos < b.pos;
             });

        /*
         * Only special positions in (m, n] can affect the answer.
         */
        int K = t;

        for (const auto& s : sp) {
            if (s.pos > m && s.pos <= n) {
                K = max(K, s.t);
            }
        }

        /*
         * K = 0:
         *
         * ordinary recurrence is empty sum = 0,
         * and every relevant special recurrence also has order 0.
         *
         * Since n > m, answer must be 0.
         */
        if (K == 0) {
            cout << "Case " << tc << ": 0\n";
            continue;
        }

        /*
         * Position -> special rule.
         * Useful during the short O(K) initialization stage.
         */
        unordered_map<int64, int> specialId;
        specialId.reserve(q * 2 + 10);

        for (int i = 0; i < q; ++i) {
            specialId[sp[i].pos] = i;
        }

        /*
         * Ordinary recurrence padded to K terms:
         *
         * f[x] =
         * C[0] f[x-1] +
         * C[1] f[x-2] + ...
         * C[K-1] f[x-K]
         */
        vector<int64> C(K, 0);

        for (int i = 0; i < t; ++i) {
            C[i] = ordinary[i];
        }

        /*
         * state:
         *
         * [f[cur-K+1], ..., f[cur]]
         */
        vector<int64> state;
        int64 cur;

        /*
         * If K <= m, boundary values already provide K history values.
         */
        if (K <= m) {
            cur = m;

            state.resize(K);

            for (int j = 0; j < K; ++j) {
                state[j] = init[m - K + 1 + j];
            }
        }
        else {
            /*
             * Need to generate f[m+1] ... f[K] sequentially.
             *
             * K <= 100, so this is cheap.
             */
            int64 upto = min<int64>(K, n);

            vector<int64> f((int)upto + 1, 0);

            for (int i = 1; i <= m; ++i) {
                f[i] = init[i];
            }

            for (int x = m + 1; x <= upto; ++x) {
                int64 val = 0;

                auto it = specialId.find(x);

                if (it != specialId.end()) {
                    const Special& s = sp[it->second];

                    for (int lag = 1; lag <= s.t; ++lag) {
                        val += s.c[lag - 1] * f[x - lag] % MOD;

                        if (val >= MOD)
                            val -= MOD;
                    }
                }
                else {
                    for (int lag = 1; lag <= t; ++lag) {
                        val += ordinary[lag - 1] * f[x - lag] % MOD;

                        if (val >= MOD)
                            val -= MOD;
                    }
                }

                f[x] = val;
            }

            /*
             * Target lies inside the small initialization range.
             */
            if (n <= K) {
                cout << "Case " << tc << ": " << f[(int)n] << '\n';
                continue;
            }

            cur = K;

            state.resize(K);

            for (int j = 0; j < K; ++j) {
                state[j] = f[j + 1];
            }
        }

        /*
         * Polynomial multiplication modulo
         *
         * x^K =
         * C[0] x^(K-1) +
         * C[1] x^(K-2) + ... +
         * C[K-1]
         */
        auto polyMul = [&](const vector<int64>& A,
                           const vector<int64>& B) {
            vector<int64> tmp(2 * K - 1, 0);

            // Normal multiplication
            for (int i = 0; i < K; ++i) {
                if (A[i] == 0)
                    continue;

                for (int j = 0; j < K; ++j) {
                    if (B[j] == 0)
                        continue;

                    tmp[i + j] =
                        (tmp[i + j] + A[i] * B[j]) % MOD;
                }
            }

            // Reduce high degree terms
            for (int deg = 2 * K - 2; deg >= K; --deg) {
                int64 v = tmp[deg];

                if (v == 0)
                    continue;

                /*
                 * x^deg =
                 *
                 * C[0] x^(deg-1)
                 * + C[1] x^(deg-2)
                 * + ...
                 * + C[K-1] x^(deg-K)
                 */
                for (int lag = 1; lag <= K; ++lag) {
                    if (C[lag - 1] == 0)
                        continue;

                    tmp[deg - lag] =
                        (tmp[deg - lag]
                         + v * C[lag - 1]) % MOD;
                }
            }

            tmp.resize(K);
            return tmp;
        };

        /*
         * Multiply a polynomial by x modulo the characteristic
         * polynomial.
         *
         * This only costs O(K), rather than O(K^2).
         */
        auto mulX = [&](const vector<int64>& A) {
            vector<int64> B(K, 0);

            // Shift all terms by one degree
            for (int i = 1; i < K; ++i) {
                B[i] = A[i - 1];
            }

            // Overflow term A[K-1] * x^K
            int64 overflow = A[K - 1];

            if (overflow != 0) {
                for (int lag = 1; lag <= K; ++lag) {
                    if (C[lag - 1] == 0)
                        continue;

                    /*
                     * C[lag-1] contributes to x^(K-lag)
                     */
                    B[K - lag] =
                        (B[K - lag]
                         + overflow * C[lag - 1]) % MOD;
                }
            }

            return B;
        };

        /*
         * Precompute
         *
         * x^(2^0), x^(2^1), ..., x^(2^31)
         *
         * modulo characteristic polynomial.
         */
        const int BITS = 32;

        vector<vector<int64>> pw(BITS,
                                 vector<int64>(K, 0));

        vector<int64> one(K, 0);
        one[0] = 1;

        // x mod P(x)
        pw[0] = mulX(one);

        for (int b = 1; b < BITS; ++b) {
            pw[b] = polyMul(pw[b - 1], pw[b - 1]);
        }

        /*
         * Calculate x^d mod P(x)
         */
        auto powerX = [&](int64 d) {
            vector<int64> result(K, 0);
            result[0] = 1;

            int bit = 0;

            while (d > 0) {
                if (d & 1LL) {
                    result = polyMul(result, pw[bit]);
                }

                d >>= 1;
                ++bit;
            }

            return result;
        };

        /*
         * Advance the current state by d ordinary recurrence steps.
         *
         * Before:
         * state = [f[cur-K+1], ..., f[cur]]
         *
         * After:
         * state = [f[cur+d-K+1], ..., f[cur+d]]
         */
        auto advanceState = [&](int64 d) {
            if (d == 0)
                return;

            /*
             * For a very short interval, direct recurrence is cheaper
             * than polynomial exponentiation.
             */
            if (d <= K) {
                while (d--) {
                    int64 val = 0;

                    for (int lag = 1; lag <= K; ++lag) {
                        if (C[lag - 1] == 0)
                            continue;

                        val += C[lag - 1]
                               * state[K - lag] % MOD;

                        if (val >= MOD)
                            val -= MOD;
                    }

                    for (int i = 0; i + 1 < K; ++i) {
                        state[i] = state[i + 1];
                    }

                    state[K - 1] = val;
                }

                return;
            }

            /*
             * Let
             *
             * g[j] = old state sequence beginning from
             * f[cur-K+1].
             *
             * New state is:
             *
             * g[d], g[d+1], ..., g[d+K-1].
             */

            vector<int64> base = state;

            // coeff represents x^d
            vector<int64> coeff = powerX(d);

            vector<int64> nextState(K);

            for (int j = 0; j < K; ++j) {
                int64 val = 0;

                for (int i = 0; i < K; ++i) {
                    if (coeff[i] == 0 ||
                        base[i] == 0)
                        continue;

                    val += coeff[i] * base[i] % MOD;

                    if (val >= MOD)
                        val -= MOD;
                }

                nextState[j] = val;

                if (j + 1 < K) {
                    // x^(d+j+1)
                    coeff = mulX(coeff);
                }
            }

            state.swap(nextState);
        };

        /*
         * Process each relevant special point.
         */
        for (const Special& s : sp) {
            if (s.pos <= cur || s.pos > n)
                continue;

            /*
             * First move to s.pos - 1 using ordinary recurrence only.
             */
            int64 dist = s.pos - 1 - cur;

            advanceState(dist);

            cur = s.pos - 1;

            /*
             * Now:
             *
             * state =
             * [f[s.pos-K], ..., f[s.pos-1]]
             *
             * and
             *
             * f[s.pos-i] = state[K-i].
             */
            int64 val = 0;

            for (int lag = 1; lag <= s.t; ++lag) {
                val += s.c[lag - 1]
                       * state[K - lag] % MOD;

                if (val >= MOD)
                    val -= MOD;
            }

            /*
             * Push the special value into state.
             */
            for (int i = 0; i + 1 < K; ++i) {
                state[i] = state[i + 1];
            }

            state[K - 1] = val;

            cur = s.pos;
        }

        /*
         * Final ordinary interval.
         */
        if (cur < n) {
            advanceState(n - cur);
            cur = n;
        }

        cout << "Case " << tc << ": "
             << state[K - 1] % MOD << '\n';
    }

    return 0;
}