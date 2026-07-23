#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

using int64 = long long;
using i128 = __int128_t;  // 费用可能很大，用 __int128 存答案

/*
 * 题意概要（搭桥 + 飞行）：
 * - 有 n 根木桩，高度 a[1..n]
 * - 可以选择在前缀 [1, r] 上搭一座桥，桥面高度为 V：
 *     · 两端木桩 1 和 r：可以把高度升高到 V，每升高 1 单位花费 x
 *     · 任意木桩：可以把高度降低到 V，每降低 1 单位花费 y
 *     · 中间木桩不能升高（所以最优 V 一定 ≤ 所有中间木桩高度；
 *       实现上通过“权值”找最优 V，效果等价）
 * - 剩余木桩 r+1..n 不用桥，直接“飞过去”，每根花费 k
 * - 也可以完全不搭桥（相当于 r=1），费用为 (n-1)*k
 * - 求最小总费用
 *
 * 做法：枚举右端点 r，对每个 r 用树状数组快速求最优桥面高度 V 及费用。
 */

// ========================= 树状数组（Fenwick / BIT） =========================
// 支持：单点加、前缀和、以及“第 k 小权值位置”（二分在树上做）
struct Fenwick {
    int n;
    vector<int64> bit;  // bit[i] 维护一段长度为 lowbit(i) 的区间和；下标从 1 开始

    Fenwick(int n = 0) { init(n); }

    void init(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }

    // 单点更新：把位置 pos 上的值加上 val
    // pos += pos & -pos 即跳到所有覆盖 pos 的祖先节点
    void add(int pos, int64 val) {
        for (; pos <= n; pos += pos & -pos) {
            bit[pos] += val;
        }
    }

    // 查询前缀和：原数组 [1..pos] 的和
    // pos -= pos & -pos 把区间拆成若干个树状数组节点
    int64 sumPrefix(int pos) const {
        int64 res = 0;
        for (; pos > 0; pos -= pos & -pos) {
            res += bit[pos];
        }
        return res;
    }

    // 树上二分：返回最小的 idx，使得 prefix_sum(idx) >= target
    // 常用于“带权第 k 小”：这里 target 就是要累积的权重门槛
    int kth(int64 target) const {
        int pos = 0;   // 当前已确定的前缀右端点（还差一步）
        int64 cur = 0; // 已累积的权重和

        // 找到不超过 n 的最大 2 的幂，作为二分步长起点
        int step = 1;
        while ((step << 1) <= n) step <<= 1;

        // 从大步长到小步长尝试往右跳
        for (; step > 0; step >>= 1) {
            int nxt = pos + step;
            // 若跳到 nxt 后，前缀权重仍 < target，说明答案还在更右边
            if (nxt <= n && cur + bit[nxt] < target) {
                pos = nxt;
                cur += bit[nxt];
            }
        }
        // pos 是最后一个“前缀和 < target”的位置，答案是 pos+1
        return pos + 1;
    }
};

// 输出 __int128（标准库没有直接支持 cout << __int128）
void print128(i128 x) {
    if (x == 0) {
        cout << 0;
        return;
    }
    if (x < 0) {
        cout << '-';
        x = -x;
    }

    string s;
    while (x > 0) {
        s.push_back(char('0' + x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        int64 x, y, k;  // x: 升高单价；y: 降低单价；k: 飞行单价
        cin >> n >> x >> y >> k;

        vector<int64> a(n + 1);
        vector<int64> vals;  // 用于离散化的高度列表
        vals.reserve(n);

        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            vals.push_back(a[i]);
        }

        // -------- 离散化 --------
        // 高度可能很大/很稀疏，树状数组下标需要压到 1..m
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        // 之后：vals[0] < vals[1] < ... < vals[m-1]
        // getId(h) 返回 h 在树状数组中的下标（1-based）

        auto getId = [&](int64 value) {
            return int(lower_bound(vals.begin(), vals.end(), value) - vals.begin()) + 1;
        };

        int m = (int)vals.size();

        // 三棵树状数组，都建在“离散化后的高度坐标”上：
        // fwWeight：每个高度位置上的“决策权重”，用来找最优桥面高度 V
        // fwCount ：每个高度上有多少根木桩
        // fwSum   ：每个高度上木桩高度之和（同高度多根就累加多次）
        Fenwick fwWeight(m), fwCount(m), fwSum(m);

        // -------- 关于 fwWeight 与最优 V --------
        // 桥费用关于 V 的“斜率”大致为：
        //   降低部分：每升高 V，已高于 V 的木桩各少花 y  → 斜率贡献 -y * (#高于V)
        //   升高部分：两端若低于 V，每升高 V 各多花 x     → 斜率贡献 +x * (#两端已低于V)
        // 用权值技巧：给每根木桩在其高度处放权 y；两端额外再放权 x。
        // 于是在高度从小到大扫描时，累积权值达到 r*y 的位置，就是斜率由负变正的最优 V。
        // （等价于带权中位数 / 树上二分找临界点）

        // r = 1：不搭桥，剩余 n-1 段全飞
        i128 ans = (i128)(n - 1) * k;

        if (n >= 2) {
            // 初始化区间 [1, 2]：两端都是“端点”，权重均为 x+y
            int id1 = getId(a[1]);
            int id2 = getId(a[2]);

            fwWeight.add(id1, x + y);
            fwWeight.add(id2, x + y);

            fwCount.add(id1, 1);
            fwCount.add(id2, 1);

            fwSum.add(id1, a[1]);
            fwSum.add(id2, a[2]);

            int64 totalHeightSum = a[1] + a[2];  // 当前窗口 [1..r] 高度总和

            // 枚举桥的右端点 r（桥覆盖 [1..r]）
            for (int r = 2; r <= n; ++r) {
                if (r >= 3) {
                    // 窗口右端从 r-1 扩到 r：
                    // 原来的右端点 a[r-1] 变成“中间桩”，不再允许升高，
                    // 因此要去掉它身上多出来的那份端点权重 x（只保留降低相关的 y）
                    fwWeight.add(getId(a[r - 1]), -x);

                    // 新右端点 a[r] 作为端点加入，权重 x+y，并更新计数与高度和
                    int id = getId(a[r]);
                    fwWeight.add(id, x + y);
                    fwCount.add(id, 1);
                    fwSum.add(id, a[r]);

                    totalHeightSum += a[r];
                }

                // ---- 找最优桥面高度 V ----
                // 权重门槛 = r * y（见上面斜率/带权中位数解释）
                int64 target = (int64)r * y;
                int pos = fwWeight.kth(target);  // 离散化下标
                int64 V = vals[pos - 1];         // 还原成真实高度

                // 高度 ≤ V 的木桩：个数与高度和
                int64 cntLE = fwCount.sumPrefix(pos);
                int64 sumLE = fwSum.sumPrefix(pos);

                // 高度 > V 的木桩：需要全部降到 V
                int64 cntGreater = r - cntLE;
                int64 sumGreater = totalHeightSum - sumLE;

                // 降低费用：对每根高于 V 的桩，付 y * (h_i - V)
                // 即 y * (Σh_i - cnt * V)
                i128 downCost = (i128)y * (sumGreater - cntGreater * V);

                // 升高费用：只有两端可以升高；若端点已 ≥ V 则不用升
                i128 upCost = 0;
                if (V > a[1]) upCost += (i128)x * (V - a[1]);
                if (V > a[r]) upCost += (i128)x * (V - a[r]);

                i128 bridgeCost = downCost + upCost;           // 搭桥总花费
                i128 flyCost = (i128)(n - r) * k;              // 后面 n-r 根直接飞

                ans = min(ans, bridgeCost + flyCost);
            }
        }

        print128(ans);
        cout << '\n';
    }

    return 0;
}
