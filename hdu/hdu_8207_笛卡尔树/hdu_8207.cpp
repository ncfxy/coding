#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

/*
 * 题意简述：
 *   有 n 张卡，余额为 a[i]。定义 F(b) = 所有子数组最大值之和。
 *   每次询问给你 p 刀钱，要分配到这些卡上（可全给一张），使 F 最大。
 *
 * 关键结论：最优一定是「把全部 p 都存到某一张卡」。
 * 所以每个询问只需枚举 pos = 0..n-1，算 F(a + p*e_pos)，取最大。
 *
 * 做法骨架：
 *   1. 建最大笛卡尔树，算出原数组的 base = F(a)
 *   2. 对每个 pos，分析「存钱到 pos」时，增量 D(p) 如何随 p 变化
 *   3. 询问按 p 排序，扫一遍事件，更新 ans
 */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<ll> a(n);
        for (auto &x : a) cin >> x;

        int q;
        cin >> q;

        vector<ll> p(q);
        for (auto &x : p) cin >> x;

        // ============================================================
        // 第一步：用单调栈 O(n) 建「最大笛卡尔树」
        //
        // 性质：
        //   - 中序遍历 = 原数组下标顺序（左子树下标都 < u，右子树都 > u）
        //   - 堆性质：父节点余额 >= 子节点余额（最大堆）
        //   - 平局：相同余额时，下标更大的优先级更高（当父亲）
        //
        // 直观含义（非常重要）：
        //   节点 u 的子树，恰好对应原数组一段连续区间 [L,R]，
        //   且 u 是这段区间里「被选为最大值代表」的那个位置。
        // ============================================================
        vector<int> parent(n, -1), lc(n, -1), rc(n, -1), st;
        // parent[i]：父亲下标；lc/rc：左右儿子；st：单调栈，维护当前树的最右链
        st.reserve(n);

        for (int i = 0; i < n; ++i) {
            int last = -1;  // 最近被弹出的节点，稍后会挂到 i 的左儿子

            // 栈顶比 i「弱」就弹出：值更小，或值相同但下标更小
            // 弹出后，这些弱节点最终会挂在 i 的左子树里
            while (!st.empty()) {
                int x = st.back();
                if (a[x] < a[i] || (a[x] == a[i] && x < i)) {
                    last = x;
                    st.pop_back();
                } else {
                    break;
                }
            }

            // 栈里还剩东西：栈顶是 i 的父亲，i 成为栈顶的右儿子
            if (!st.empty()) {
                parent[i] = st.back();
                rc[st.back()] = i;
            }

            // last 是被弹出的那棵子树的根，挂到 i 的左儿子
            if (last != -1) {
                parent[last] = i;
                lc[i] = last;
            }

            st.push_back(i);
        }

        // 栈底就是整棵树的根（最左边、也是全局最大代表）
        int root = st[0];

        // ============================================================
        // 第二步：算每个节点左右子树大小 ls[i]、rs[i]
        //
        // 因为中序 = 下标顺序，所以：
        //   节点 u 子树覆盖的区间是 [u - ls[u], u + rs[u]]
        //
        // 以 u 为「最大值代表」的子数组个数 = (ls[u]+1) * (rs[u]+1)
        //   - 左端点可取 u 左边 ls[u]+1 个位置（含自己）
        //   - 右端点可取 u 右边 rs[u]+1 个位置（含自己）
        // ============================================================
        vector<ll> ls(n, 0), rs(n, 0);
        vector<int> order, dfs = {root};

        // 先序遍历记下 order，再倒序处理 = 等价于后序（先算儿子再算父亲）
        while (!dfs.empty()) {
            int u = dfs.back();
            dfs.pop_back();
            order.push_back(u);

            if (lc[u] != -1) dfs.push_back(lc[u]);
            if (rc[u] != -1) dfs.push_back(rc[u]);
        }

        for (int i = (int)order.size() - 1; i >= 0; --i) {
            int u = order[i];
            if (lc[u] != -1) {
                int v = lc[u];
                // 左子树大小 = 左儿子整棵子树的节点数
                ls[u] = ls[v] + rs[v] + 1;
            }
            if (rc[u] != -1) {
                int v = rc[u];
                rs[u] = ls[v] + rs[v] + 1;
            }
        }

        // 原数组所有子数组最大值之和
        // F(a) = Σ a[i] * (以 i 为最大值代表的子数组个数)
        ll base = 0;
        for (int i = 0; i < n; ++i) {
            base += a[i] * (ls[i] + 1) * (rs[i] + 1);
        }

        // ============================================================
        // 第三步：询问按 p 从小到大排序，方便后面扫事件
        // ============================================================
        vector<pair<ll, int>> queries;
        for (int i = 0; i < q; ++i) {
            queries.push_back({p[i], i});  // {钱数, 原询问编号}
        }
        sort(queries.begin(), queries.end());

        // 初始答案至少是 base（p=0 或不加钱也一样）
        // 后面枚举「全存到某张卡」再取 max
        vector<ll> ans(q, base);

        // ============================================================
        // 第四步：枚举把全部钱都存到 pos
        //
        // 设 b = a[pos] + p。只有「包含 pos」的子数组可能变大。
        // 对区间 [L,R]（含 pos），增量是 max(0, b - 原区间最大值)。
        //
        // 把增量看成 p 的函数 D(p)：它是分段一次函数。
        // 当 b 刚超过某个高度 h 时，能「被 pos 盖住」的连续区间会突然变大，
        // 斜率（每多存 1 刀，答案多涨多少）也会阶跃变大。
        //
        // 这些高度恰好是：笛卡尔树上，从 pos 走到根的祖先们的余额。
        // 跨过祖先 top 后，覆盖区间变成 top 的整棵子树区间。
        // ============================================================
        for (int pos = 0; pos < n; ++pos) {
            /*
             * events[k] = {需要的最少存钱量 need, 跨过该高度后的斜率 slope}
             *
             * 含义：当存钱量 p >= need 时，斜率变为 slope。
             * 事件按 need 从小到大排列（因为我们从 pos 往根走，高度递增）。
             */
            vector<pair<ll, ll>> events;

            int u = pos;
            while (u != -1) {
                ll h = a[u];   // 当前这一层的高度（余额）
                int top = u;   // 同高度链上「最高」的那个祖先

                // 相同高度必须一起跨过：
                // 余额从 h 涨到 h+1 时，所有原本 = h 的位置同时「被压过」，
                // 覆盖区间会直接扩到同高度链的最顶祖先的子树。
                u = parent[u];
                while (u != -1 && a[u] == h) {
                    top = u;
                    u = parent[u];
                }

                // top 的子树中序区间 = [L, R]
                // （中序=下标，左子树有 ls[top] 个点，右子树有 rs[top] 个点）
                ll L = top - ls[top];
                ll R = top + rs[top];

                // 包含 pos、且完全落在 [L,R] 内的子数组个数
                // = 左端点可选 (pos-L+1) 种 × 右端点可选 (R-pos+1) 种
                // 这就是「b 刚超过 h」之后的斜率
                ll slope = (pos - L + 1) * (R - pos + 1);

                // 要让 a[pos]+p 超过高度 h，至少需要存 h - a[pos]
                // （注意：第一个事件 need=0，因为一开始就已经「占据」自己这一层）
                events.push_back({h - a[pos], slope});
            }

            // ---- 对当前 pos，用双指针扫排序后的询问，算增量 D(p) ----
            // D(p) 是分段一次函数：每段斜率为 slope，在事件点处斜率跳变
            ll currentValue = 0;  // 已经算到 lastP 处的增量 D(lastP)
            ll lastP = 0;         // 上一个「结算点」的 p
            ll slope = events[0].second;  // 当前段斜率（从 p=0 开始）
            int ptr = 1;          // 下一个待处理的事件下标

            for (size_t qi = 0; qi < queries.size(); ++qi) {
                ll nowP = queries[qi].first;
                int id = queries[qi].second;

                // 把所有 need <= nowP 的事件都处理掉：先把上一段积分完，再换斜率
                while (ptr < (int)events.size() &&
                       events[ptr].first <= nowP) {
                    ll nextP = events[ptr].first;
                    // 在 [lastP, nextP] 上斜率为 slope，积分加到增量里
                    currentValue += slope * (nextP - lastP);
                    lastP = nextP;
                    slope = events[ptr].second;  // 跨过该高度，斜率变大
                    ++ptr;
                }

                // 从 lastP 再积到 nowP，得到 D(nowP)
                ll gain = currentValue + slope * (nowP - lastP);
                // 全存到 pos 时的答案 = base + 增量；对每个询问取所有 pos 的最大
                ans[id] = max(ans[id], base + gain);
            }
        }

        for (ll x : ans) {
            cout << x << '\n';
        }
    }

    return 0;
}
