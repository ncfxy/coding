#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

using ll = long long;

struct Edge {
    int u, v;
    ll w;
};

struct AdjEdge {
    int to;
    ll w;
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    int tc = 0;

    while (cin >> n >> m) {
        ++tc;

        vector<int> color(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> color[i];
        }

        vector<Edge> edges(m);
        vector<vector<AdjEdge>> g(n + 1);
        vector<int> degree(n + 1, 0);

        for (int i = 0; i < m; ++i) {
            int u, v;
            ll w;
            cin >> u >> v >> w;

            edges[i] = {u, v, w};

            g[u].push_back({v, w});
            g[v].push_back({u, w});

            ++degree[u];
            ++degree[v];
        }

        // 根号阈值
        int B = (int)sqrt(2.0 * m) + 1;

        // heavyId[x] = x 是第几个重点
        // -1 表示轻点
        vector<int> heavyId(n + 1, -1);
        vector<int> heavyVertex;

        for (int i = 1; i <= n; ++i) {
            if (degree[i] > B) {
                heavyId[i] = (int)heavyVertex.size();
                heavyVertex.push_back(i);
            }
        }

        int H = heavyVertex.size();

        /*
         * heavySum[id][c]:
         * 重点 heavyVertex[id] 连向颜色 c 的所有边的权值和
         */
         vector<array<ll, 2>> heavySum(H);
         for (int i = 0; i < H; ++i) {
             heavySum[i][0] = heavySum[i][1] = 0;
         }

         /*
         * heavyNeighbor[x]:
         * (重点id, x 与该重点之间所有边的权值和)
         *
         * 初始先把每条边加进去，后面排序合并重边。
         */
        vector<vector<pair<int, ll>>> heavyNeighbor(n + 1);

        ll ans00 = 0;
        ll ans01 = 0;
        ll ans11 = 0;

        for (const auto &e : edges) {
            int u = e.u;
            int v = e.v;
            ll w = e.w;

            // 初始化全局答案
            if (color[u] == 0 && color[v] == 0) {
                ans00 += w;
            } else if (color[u] == 1 && color[v] == 1) {
                ans11 += w;
            } else {
                ans01 += w;
            }

            // 初始化重点维护的信息
            if (heavyId[u] != -1) {
                heavySum[heavyId[u]][color[v]] += w;
            }

            if (heavyId[v] != -1) {
                heavySum[heavyId[v]][color[u]] += w;
            }

            // x 修改时，要修改所有与 x 相邻的重点
            if (heavyId[v] != -1) {
                heavyNeighbor[u].push_back({heavyId[v], w});
            }

            if (heavyId[u] != -1) {
                heavyNeighbor[v].push_back({heavyId[u], w});
            }
        }

        /*
         * 合并：
         * 如果 x 和同一个重点之间存在多条边，
         * 将它们的权值相加。
         */
         for (int x = 1; x <= n; ++x) {
            auto &vec = heavyNeighbor[x];

            if (vec.empty()) continue;

            sort(vec.begin(), vec.end());

            int k = 0;

            for (int i = 0; i < (int)vec.size(); ++i) {
                if (k > 0 && vec[k - 1].first == vec[i].first) {
                    vec[k - 1].second += vec[i].second;
                } else {
                    vec[k++] = vec[i];
                }
            }

            vec.resize(k);
        }

        int q;
        cin >> q;

        cout << "Case " << tc << ":\n";

        while (q--) {
            string op;
            cin >> op;

            if (op == "Change") {
                int x;
                cin >> x;

                int oldColor = color[x];
                int newColor = oldColor ^ 1;

                ll sum0 = 0;
                ll sum1 = 0;

                /*
                 * 求 x 连向两种颜色的边权和
                 */
                if (heavyId[x] != -1) {
                    // 重点 O(1)
                    int id = heavyId[x];
                    sum0 = heavySum[id][0];
                    sum1 = heavySum[id][1];
                } else {
                    // 轻点，直接扫描邻边 O(B)
                    for (const auto &e : g[x]) {
                        if (color[e.to] == 0)
                            sum0 += e.w;
                        else
                            sum1 += e.w;
                    }
                }

                /*
                 * 修改全局三个答案
                 */
                if (oldColor == 0) {
                    // 0 -> 1

                    // 连接黑点：
                    // 00 -> 01
                    ans00 -= sum0;
                    ans01 += sum0;

                    // 连接白点：
                    // 01 -> 11
                    ans01 -= sum1;
                    ans11 += sum1;
                } else {
                    // 1 -> 0

                    // 连接黑点：
                    // 01 -> 00
                    ans01 -= sum0;
                    ans00 += sum0;

                    // 连接白点：
                    // 11 -> 01
                    ans11 -= sum1;
                    ans01 += sum1;
                }

                /*
                 * x 的颜色发生变化，会影响所有与 x 相邻重点的
                 * heavySum。
                 */
                for (const auto &p : heavyNeighbor[x]) {
                    int id = p.first;
                    ll w = p.second;
                    heavySum[id][oldColor] -= w;
                    heavySum[id][newColor] += w;
                }

                color[x] = newColor;
            }else {
                // Asksum
                int A, Bc;
                cin >> A >> Bc;

                if (A == 0 && Bc == 0) {
                    cout << ans00 << '\n';
                } else if (A == 1 && Bc == 1) {
                    cout << ans11 << '\n';
                } else {
                    cout << ans01 << '\n';
                }
            }
        }
    }
    return 0;
}