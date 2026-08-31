#include <iostream>
#include <vector>
#include <queue>
using namespace std;

using ll = long long;

const ll INF = (1LL << 60);
const int MAXN = 200005;

struct Edge {
    int to;
    ll w;
};

vector<Edge> g[MAXN];
ll dist[MAXN];
bool vis[MAXN];

void dijkstra(int s, int n) {
    // 初始化
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        vis[i] = false;
    }

    // 小根堆：{当前距离, 节点}
    priority_queue<
        pair<ll, int>,
        vector<pair<ll, int>>,
        greater<pair<ll, int>>
    > pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        // auto [d, u] = pq.top();
        auto d = pq.top().first;
        auto u = pq.top().second;
        pq.pop();

        // 这个点已经确定过最短距离
        if (vis[u]) continue;
        vis[u] = true;

        for (auto edge : g[u]) {
            int v = edge.to;
            ll w = edge.w;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s;
    cin >> n >> m >> s;

    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;

        // 有向图
        g[u].push_back({v, w});

        // 如果是无向图，再加：
        // g[v].push_back({u, w});
    }

    dijkstra(s, n);

    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF)
            cout << -1 << '\n';
        else
            cout << dist[i] << '\n';
    }

    return 0;
}