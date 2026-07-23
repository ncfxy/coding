#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// 模数：答案对 998244353 取模
static const long long MOD = 998244353;

/*
 * 题意简述：
 *   树上三点 x,y,z 若三对两两 LCA 都等于同一个点 v，
 *   则贡献 a_x * a_y * a_z。求所有合法三元组贡献之和。
 *
 * 做法概述：
 *   对每个可能的公共 LCA 点 v 单独统计贡献。
 *   在 v 处把相关点分成若干「组」：
 *     - 组 0：只有 v 自己，组和 = a[v]
 *     - 其余组：v 的每个儿子子树，组和 = 该子树权值和
 *   合法三元组 <=> 三点分别来自三个不同的组。
 *   因此 v 的贡献 = 各组和的「选三个不同组的乘积之和」。
 *   用 s1/s2/s3 增量维护，每个点 O(度数)，总 O(n)。
 */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        // 邻接表建无向树
        vector<vector<int>> g(n + 1);
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        // 点权，先取模避免后续乘法溢出逻辑变复杂
        vector<long long> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            a[i] %= MOD;
        }

        // ---------- 第一步：以 1 为根，非递归 DFS ----------
        // 得到 parent[] 与 DFS 序 order[]。
        // 不用递归是为了防止树退化成链时系统栈溢出。
        vector<int> parent(n + 1, 0), order;
        order.reserve(n);

        stack<int> st;
        st.push(1);
        parent[1] = -1; // 根的父亲记为 -1，表示没有父亲

        while (!st.empty()) {
            int v = st.top();
            st.pop();
            order.push_back(v); // 先序：父在前、子在后

            for (int u : g[v]) {
                if (u == parent[v]) continue; // 跳过连回父亲的边
                parent[u] = v;
                st.push(u);
            }
        }

        // ---------- 第二步：自底向上统计每个点的贡献 ----------
        // subtreeSum[v]：以 v 为根的子树权值和
        // ans：最终答案
        vector<long long> subtreeSum(n + 1, 0);
        long long ans = 0;

        // order 是先序，逆序遍历 => 先处理叶子、后处理祖先
        // 保证处理 v 时，所有儿子的 subtreeSum 已经算好
        for (int idx = n - 1; idx >= 0; --idx) {
            int v = order[idx];

            // 在 v 处维护「已处理各组」的对称和：
            //   s1 = sum x_i
            //   s2 = sum_{i<j} x_i * x_j
            //   s3 = sum_{i<j<k} x_i * x_j * x_k   <-- 即 v 的贡献
            // 初始先放入「组 0」：节点 v 自身
            long long s1 = a[v];
            long long s2 = 0;
            long long s3 = 0;

            // 再依次加入每个儿子子树作为一个新组
            for (int u : g[v]) {
                if (parent[u] != v) continue; // 无向边里只保留儿子方向

                long long x = subtreeSum[u]; // 新组和 = 儿子 u 的子树权值和

                // 加入新组 x 时的增量更新（顺序必须是 s3 -> s2 -> s1）：
                //   新的三项积 = 旧的两项积 * x
                //   新的两项积 = 旧的一项和 * x
                //   新的一项和 = 旧的一项和 + x
                s3 = (s3 + s2 * x) % MOD;
                s2 = (s2 + s1 * x) % MOD;
                s1 = (s1 + x) % MOD;
            }

            // 此时 s1 恰好等于 v 子树的全部权值和，留给父亲当「一个组和」
            subtreeSum[v] = s1;
            // s3 就是「三对 LCA 都等于 v」的所有三元组贡献
            ans = (ans + s3) % MOD;
        }

        cout << ans << '\n';
    }

    return 0;
}
