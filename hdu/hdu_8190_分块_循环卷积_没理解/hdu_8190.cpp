
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long;

const double PI = acos(-1.0);

struct CP {
    double r, i;

    CP(double _r = 0, double _i = 0) : r(_r), i(_i) {}
};

inline CP add(CP a, CP b) {
    return CP(a.r + b.r, a.i + b.i);
}

inline CP sub(CP a, CP b) {
    return CP(a.r - b.r, a.i - b.i);
}

inline CP mul(CP a, CP b) {
    return CP(
        a.r * b.r - a.i * b.i,
        a.r * b.i + a.i * b.r
    );
}

inline CP conj_cp(CP a) {
    return CP(a.r, -a.i);
}

struct FFT {
    int n, lg;
    vector<int> rev;
    vector<CP> roots;

    FFT(int _n = 1) {
        init(_n);
    }

    void init(int _n) {
        n = _n;
        lg = __builtin_ctz(n);

        rev.resize(n);
        rev[0] = 0;

        for (int i = 1; i < n; i++) {
            rev[i] =
                (rev[i >> 1] >> 1)
                | ((i & 1) << (lg - 1));
        }

        roots.resize(n / 2);

        for (int k = 0; k < n / 2; k++) {
            double ang = -2.0 * PI * k / n;
            roots[k] = CP(cos(ang), sin(ang));
        }
    }

    void transform(vector<CP>& a, bool inverse) const {
        for (int i = 0; i < n; i++) {
            if (i < rev[i]) {
                swap(a[i], a[rev[i]]);
            }
        }

        for (int len = 2; len <= n; len <<= 1) {
            int half = len >> 1;
            int step = n / len;

            for (int st = 0; st < n; st += len) {
                for (int j = 0; j < half; j++) {
                    CP w = roots[j * step];
                    if (inverse) w.i = -w.i;

                    CP u = a[st + j];
                    CP v = mul(a[st + j + half], w);

                    a[st + j] = add(u, v);
                    a[st + j + half] = sub(u, v);
                }
            }
        }

        if (inverse) {
            double invn = 1.0 / n;
            for (auto& x : a) {
                x.r *= invn;
                x.i *= invn;
            }
        }
    }
};

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int& x : a) cin >> x;

    vector<ll> ans(n + 1, 0);

    /*
     * FFT 长度。
     *
     * 我们使用循环相关：
     * 正差 k 存放在 k，
     * 负差 -k 存放在 L-k。
     *
     * L > 2n 后二者不会冲突。
     */
    int L = 1;
    while (L <= 2 * n) L <<= 1;

    /*
     * 理论上 B = Theta(sqrt(n log n))。
     *
     * 实际 FFT 的常数比同块暴力大，
     * 所以适当把 B 调大一点。
     */
    int B = (int)(
        1.2 * sqrt((double)L * log2((double)L))
    );

    B = max(B, 1);
    B = min(B, n);

    int block_cnt = (n + B - 1) / B;

    /*
     * Part 1:
     * i,j 在同一块。
     */
    for (int b = 0; b < block_cnt; b++) {
        int l = b * B;
        int r = min(n, l + B);

        for (int j = l; j < r; j++) {
            int aj = a[j];

            for (int i = l; i < j; i++) {
                int d = a[i] - aj;

                if (d >= 0) {
                    ++ans[d];
                }
            }
        }
    }

    /*
     * 如果只有一个块，不存在异块数对。
     */
    if (block_cnt == 1) {
        for (int k = 0; k <= n; k++) {
            if (k) cout << ' ';
            cout << ans[k];
        }
        cout << '\n';
        return;
    }

    FFT fft(L);

    /*
     * prefix:
     *   前面所有块 FFT 的和。
     *
     * total:
     *   所有异块贡献的频域结果。
     */
    vector<CP> prefix(L, CP(0, 0));
    vector<CP> total(L, CP(0, 0));

    /*
     * packed:
     *   实部塞第一个块，
     *   虚部塞第二个块。
     */
    vector<CP> packed(L);

    for (int b = 0; b < block_cnt; b += 2) {
        fill(packed.begin(), packed.end(), CP(0, 0));

        // 第 b 块 -> 实部
        int l1 = b * B;
        int r1 = min(n, l1 + B);

        for (int i = l1; i < r1; i++) {
            packed[a[i]].r += 1.0;
        }

        bool has_second = (b + 1 < block_cnt);

        // 第 b+1 块 -> 虚部
        if (has_second) {
            int l2 = (b + 1) * B;
            int r2 = min(n, l2 + B);

            for (int i = l2; i < r2; i++) {
                packed[a[i]].i += 1.0;
            }
        }

        fft.transform(packed, false);

        /*
         * 一次 FFT 中恢复两个实数组的 FFT。
         *
         * 设
         *
         *   H = FFT(f + i g)
         *
         * 则
         *
         *   F[k] = (H[k] + conj(H[-k])) / 2
         *
         *   G[k] = (H[k] - conj(H[-k])) / (2i)
         */
        for (int k = 0; k < L; k++) {
            int nk = (L - k) & (L - 1);

            CP z = packed[k];
            CP cz = conj_cp(packed[nk]);

            // FFT of block b
            CP F(
                (z.r + cz.r) * 0.5,
                (z.i + cz.i) * 0.5
            );

            /*
             * 当前块作为右块。
             *
             * coefficient of:
             *
             *   prefix(z) * F(z^{-1})
             *
             * FFT(F(z^{-1})) = conj(FFT(F)).
             */
            CP prod = mul(prefix[k], conj_cp(F));

            total[k].r += prod.r;
            total[k].i += prod.i;

            prefix[k].r += F.r;
            prefix[k].i += F.i;

            if (has_second) {
                CP dif(
                    z.r - cz.r,
                    z.i - cz.i
                );

                /*
                 * dif / (2i)
                 *
                 * (x + iy) / (2i)
                 * = y/2 - i*x/2
                 */
                CP G(
                    dif.i * 0.5,
                    -dif.r * 0.5
                );

                /*
                 * 注意这里 prefix 已经加入了 F，
                 * 因此自然会统计：
                 *
                 * block b -> block b+1
                 */
                CP prod2 = mul(prefix[k], conj_cp(G));

                total[k].r += prod2.r;
                total[k].i += prod2.i;

                prefix[k].r += G.r;
                prefix[k].i += G.i;
            }
        }
    }

    /*
     * 所有块对的频域结果一次性 IFFT。
     */
    fft.transform(total, true);

    /*
     * total[k]：
     *
     * 所有位于不同位置块中的
     * a_i - a_j = k, i < j
     *
     * 的数量。
     */
    for (int k = 0; k <= n; k++) {
        ll cross = llround(total[k].r);
        ans[k] += cross;
    }

    for (int k = 0; k <= n; k++) {
        if (k) cout << ' ';
        cout << ans[k];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}