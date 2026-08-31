#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>
using namespace std;

using i128 = __int128_t;

i128 ceil_div(i128 a, i128 b) {
    return (a + b - 1) / b;
}

string to_string_i128(i128 x) {
    if (x == 0) return "0";

    bool neg = x < 0;
    if (neg) x = -x;

    string s;
    while (x) {
        s.push_back(char('0' + x % 10));
        x /= 10;
    }

    if (neg) s.push_back('-');

    reverse(s.begin(), s.end());
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a1_, b1_, c1_, d1_;
    int cas = 0;

    while (cin >> a1_ >> b1_ >> c1_ >> d1_) {
        long long a2_, b2_, c2_, d2_;
        long long n_, x_, t_;

        cin >> a2_ >> b2_ >> c2_ >> d2_;
        cin >> n_ >> x_ >> t_;

        i128 A1 = a1_;
        i128 B1 = b1_;
        i128 C1 = c1_;
        i128 D1 = d1_;

        i128 A2 = a2_;
        i128 B2 = b2_;
        i128 C2 = c2_;
        i128 D2 = d2_;

        i128 N = n_;
        i128 X = x_;
        i128 T = t_;

        /*
         * 木、石、金所需要的总工作秒数。
         */
        i128 Q =
            ceil_div(B2, B1) +
            ceil_div(C2, C1) +
            ceil_div(D2, D1);

        /*
         * 训练 k 个村民后，
         * 食物目标 + 训练费用一共需要多少食物工作秒。
         */
        auto food_work = [&](i128 k) -> i128 {
            return ceil_div(A2 + k * X, A1);
        };

        /*
         * k = 0，不训练任何村民。
         * 这同时也是一个合法的答案上界。
         */
        i128 ans = ceil_div(Q + food_work(0), N);

        /*
         * 从第 j0 次训练开始，
         * 以后训练中心不会再因为缺食物而空闲。
         *
         * 需要：
         * (N+j-1) * T * A1 >= X
         */
        i128 needPop128 = ceil_div(X, A1 * T);

        // needPop <= X <= 1e5
        long long needPop = (long long)needPop128;

        long long j0 =
            max(1LL, needPop - n_ + 1);

        /*
         * s[j]    = 第 j 个村民最早开始训练的秒数
         * pref[j] = s[1] + ... + s[j]
         */
        vector<i128> s(j0 + 1);
        vector<i128> pref(j0 + 1);

        for (long long j = 1; j <= j0; ++j) {
            /*
             * 开始第 j 次训练前，
             * 至少需要采集 jX 食物。
             */
            i128 needFoodSeconds =
                ceil_div((i128)j * X, A1);

            /*
             * 在第 s 秒开始前，可用总工作秒数：
             *
             * (N+j-1)s
             * - N
             * - sum(s_i)
             * - (j-1)T
             *
             * 要 >= needFoodSeconds
             */
            i128 numerator =
                needFoodSeconds
                + N
                + pref[j - 1]
                + (i128)(j - 1) * T;

            i128 byFood =
                ceil_div(numerator, N + j - 1);

            /*
             * 城镇中心串行训练。
             */
            i128 byTownCenter;

            if (j == 1)
                byTownCenter = 1;
            else
                byTownCenter = s[j - 1] + T;

            s[j] = max(byFood, byTownCenter);
            pref[j] = pref[j - 1] + s[j];
        }

        /*
         * 枚举进入稳定连续训练阶段之前的所有 k。
         *
         * 总数最多 1e5。
         */
        for (long long k = 1; k < j0; ++k) {
            /*
             * 到 H 秒时总工作秒：
             *
             * NH + sum(H-s_i-T+1)
             *
             * = (N+k)H - sum(s_i) - k(T-1)
             */
            i128 required =
                Q
                + food_work(k)
                + pref[k]
                + (i128)k * (T - 1);

            i128 byWork =
                ceil_div(required, N + k);

            /*
             * 第 k 个村民必须已经训练完成。
             */
            i128 byCompletion =
                s[k] + T;

            i128 cur =
                max(byWork, byCompletion);

            ans = min(ans, cur);
        }

        /*
         * 从 j0 开始：
         *
         * s_k = s0 + (k-j0)T
         */
        const i128 J0 = j0;
        const i128 s0 = s[j0];
        const i128 S0 = pref[j0];

        auto start_k = [&](i128 k) -> i128 {
            return s0 + (k - J0) * T;
        };

        /*
         * S_k = sum_{i=1}^k s_i
         *
         * 后半部分为等差数列。
         */
        auto sum_start = [&](i128 k) -> i128 {
            i128 m = k - J0;

            return
                S0
                + m * s0
                + T * m * (m + 1) / 2;
        };

        /*
         * 给定 H,k，
         * 计算做完所有资源后还剩多少工作秒。
         *
         * >= 0 即可行。
         */
        auto slack = [&](i128 H, i128 k) -> i128 {
            i128 totalWork =
                (N + k) * H
                - sum_start(k)
                - k * (T - 1);

            return
                totalWork
                - Q
                - food_work(k);
        };

        /*
         * slack(H,k+1)-slack(H,k)
         */
        auto diff = [&](i128 H, i128 k) -> i128 {
            /*
             * 多训练第 k+1 个村民，
             * 它能新增这么多工作秒。
             */
            i128 addWork =
                H
                - start_k(k + 1)
                - T
                + 1;

            /*
             * 同时训练费用带来的额外食物工作秒。
             */
            i128 addFoodWork =
                food_work(k + 1)
                - food_work(k);

            return addWork - addFoodWork;
        };

        /*
         * 判断是否存在 k >= j0，
         * 可以在 H 秒内完成目标。
         */
        auto feasible_continuous =
            [&](i128 H) -> bool {

            /*
             * 连第 j0 个村民都无法完成训练。
             */
            if (H < s0 + T)
                return false;

            /*
             * s_k + T <= H
             *
             * 求最大的合法 k。
             */
            i128 K =
                J0
                + (H - s0 - T) / T;

            i128 L = J0;

            if (K < L)
                return false;

            auto ok = [&](i128 k) -> bool {
                return slack(H, k) >= 0;
            };

            if (L == K)
                return ok(L);

            /*
             * slack 是离散凹函数。
             *
             * 二分最后一个：
             *
             * diff(k) >= 0
             */
            i128 lo = L;
            i128 hi = K - 1;

            i128 pos = L - 1;

            while (lo <= hi) {
                i128 mid = (lo + hi) >> 1;

                if (diff(H, mid) >= 0) {
                    pos = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }

            /*
             * 最大值就在拐点附近。
             */
            if (ok(L))
                return true;

            if (ok(K))
                return true;

            if (pos >= L && ok(pos))
                return true;

            if (pos + 1 >= L &&
                pos + 1 <= K &&
                ok(pos + 1))
                return true;

            return false;
        };

        /*
         * ans 已经是合法上界。
         *
         * 只需要判断连续训练阶段
         * 能否提供更优答案。
         */
        if (feasible_continuous(ans)) {
            i128 lo = 0;
            i128 hi = ans;

            while (lo < hi) {
                i128 mid = (lo + hi) >> 1;

                if (feasible_continuous(mid))
                    hi = mid;
                else
                    lo = mid + 1;
            }

            ans = min(ans, lo);
        }

        cout << "Case "
             << ++cas
             << ": "
             << to_string_i128(ans)
             << '\n';
    }

    return 0;
}