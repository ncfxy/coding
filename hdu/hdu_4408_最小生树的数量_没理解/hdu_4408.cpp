#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

struct DSU {
    vector<int> fa, sz;

    DSU() {}

    DSU(int n) {
        init(n);
    }

    void init(int n) {
        fa.resize(n);
        sz.assign(n, 1);
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y) return false;

        if (sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];

        return true;
    }
};

struct Edge {
    int u, v, w;

    bool operator < (const Edge& other) const {
        return w < other.w;
    }
};

/*
 * 计算矩阵行列式 mod MOD。
 *
 * MOD 不要求是质数。
 *
 * 使用欧几里得式消元：
 *
 * Ri <- Ri - q * Rj
 *
 * 不改变 determinant，
 * 每交换两行 determinant 取反。
 */
int64 determinant_mod(vector<vector<int64>> a, int64 MOD) {
    int n = (int)a.size();

    if (n == 0) {
        return 1 % MOD;
    }

    if (MOD == 1) {
        return 0;
    }

    // 全部规范到 [0, MOD)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] %= MOD;
            if (a[i][j] < 0) {
                a[i][j] += MOD;
            }
        }
    }

    int64 ans = 1;

    for (int i = 0; i < n; ++i) {

        /*
         * 利用欧几里得算法，
         * 把第 i 列 i 以下全部消成 0。
         */
        for (int j = i + 1; j < n; ++j) {

            while (a[j][i] != 0) {

                int64 q = a[i][i] / a[j][i];

                for (int k = i; k < n; ++k) {

                    // MOD <= 1e9
                    // q、元素也都 < MOD
                    // 乘积 <= 1e18，long long 安全
                    a[i][k] =
                        (a[i][k] - q * a[j][k]) % MOD;

                    if (a[i][k] < 0) {
                        a[i][k] += MOD;
                    }
                }

                swap(a[i], a[j]);

                // 交换两行，行列式变号
                ans = (MOD - ans) % MOD;
            }
        }

        if (a[i][i] == 0) {
            return 0;
        }

        ans = ans * a[i][i] % MOD;
    }

    return ans;
}

/*
 * 给定一个缩点后的连通多重图，
 * vertices 是其中的局部顶点编号，
 * edges 是局部编号下的所有边，
 *
 * 用 Matrix-Tree 求生成树个数。
 */
int64 count_spanning_trees(
    const vector<int>& vertices,
    const vector<pair<int, int>>& edges,
    int64 MOD
) {
    int s = (int)vertices.size();

    if (s <= 1) {
        return 1 % MOD;
    }

    // local vertex id -> component-inner id
    vector<int> id(105, -1);

    for (int i = 0; i < s; ++i) {
        id[vertices[i]] = i;
    }

    vector<vector<int64>> lap(
        s,
        vector<int64>(s, 0)
    );

    for (auto [u, v] : edges) {

        int x = id[u];
        int y = id[v];

        if (x == -1 || y == -1) {
            continue;
        }

        lap[x][x]++;
        lap[y][y]++;

        lap[x][y]--;
        lap[y][x]--;
    }

    /*
     * 删除最后一行、最后一列。
     */
    vector<vector<int64>> cof(
        s - 1,
        vector<int64>(s - 1)
    );

    for (int i = 0; i < s - 1; ++i) {
        for (int j = 0; j < s - 1; ++j) {
            cof[i][j] = lap[i][j];
        }
    }

    return determinant_mod(cof, MOD);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    int64 p;

    while (cin >> n >> m >> p) {

        if (n == 0 && m == 0 && p == 0) {
            break;
        }

        vector<Edge> edges(m);

        for (auto& e : edges) {
            cin >> e.u >> e.v >> e.w;
            --e.u;
            --e.v;
        }

        sort(edges.begin(), edges.end());

        DSU global(n);

        int64 answer = 1 % p;

        int L = 0;

        while (L < m) {

            int R = L;

            while (R < m &&
                   edges[R].w == edges[L].w) {
                ++R;
            }

            /*
             * 当前权值开始处理之前，
             * global 中存放的是所有更小权值形成的连通块。
             */

            vector<pair<int, int>> cand;

            /*
             * 全局 DSU root -> 局部顶点编号
             */
            vector<int> rootId(n, -1);
            vector<int> roots;

            auto getId = [&](int root) -> int {
                if (rootId[root] == -1) {
                    rootId[root] = (int)roots.size();
                    roots.push_back(root);
                }

                return rootId[root];
            };

            /*
             * 构造当前权值缩点图。
             */
            for (int i = L; i < R; ++i) {

                int ru = global.find(edges[i].u);
                int rv = global.find(edges[i].v);

                if (ru == rv) {
                    continue;
                }

                int u = getId(ru);
                int v = getId(rv);

                cand.push_back({u, v});
            }

            int k = (int)roots.size();

            if (!cand.empty()) {

                /*
                 * 找缩点图自身的连通块。
                 */
                DSU tmp(k);

                for (auto [u, v] : cand) {
                    tmp.unite(u, v);
                }

                vector<vector<int>> compVertices(k);
                vector<vector<pair<int, int>>> compEdges(k);

                for (int i = 0; i < k; ++i) {
                    compVertices[tmp.find(i)].push_back(i);
                }

                for (auto [u, v] : cand) {
                    int r = tmp.find(u);
                    compEdges[r].push_back({u, v});
                }

                /*
                 * 每个缩点图连通块独立计算生成树个数。
                 */
                for (int r = 0; r < k; ++r) {

                    if (compVertices[r].empty()) {
                        continue;
                    }

                    int64 ways = count_spanning_trees(
                        compVertices[r],
                        compEdges[r],
                        p
                    );

                    answer = answer * ways % p;
                }
            }

            /*
             * 当前权值处理结束。
             *
             * 注意：
             * 这里要把当前权值的所有边都 union，
             * 而不是只 union 某一棵生成树的边。
             */
            for (int i = L; i < R; ++i) {
                global.unite(edges[i].u, edges[i].v);
            }

            L = R;
        }

        /*
         * 检查整个原图是否连通。
         */
        bool connected = true;

        if (n >= 1) {
            int root = global.find(0);

            for (int i = 1; i < n; ++i) {
                if (global.find(i) != root) {
                    connected = false;
                    break;
                }
            }
        }

        if (!connected) {
            cout << 0 << '\n';
        } else {
            cout << answer % p << '\n';
        }
    }

    return 0;
}