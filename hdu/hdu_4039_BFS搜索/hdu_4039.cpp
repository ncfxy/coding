#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    int N, Q;
    cin >> N >> Q;

    unordered_map<string, int> id;
    vector<string> name;
    vector<vector<int>> g;

    auto get_id = [&](const string &s) -> int {
      auto it = id.find(s);
      if (it != id.end()) {
        return it->second;
      }
      int new_id = id.size();
      id[s] = new_id;
      name.push_back(s);
      g.push_back({});
      return new_id;
    };

    // 建立无向图
    for (int i = 0; i < N; i++) {
      string a, b;
      cin >> a >> b;
      int u = get_id(a);
      int v = get_id(b);

      g[u].push_back(v);
      g[v].push_back(u);
    }

    cout << "Case " << i << ":\n";

    int V = name.size();

    while (Q--) {
      string s;
      cin >> s;
      int u = get_id(s);
      // blocked[v] = true:
      // v 是自己或者已经是直接好友，不能推荐
      vector<char> blocked(V, false);

      blocked[u] = true;
      for (int v : g[u]) {
        blocked[v] = true;
      }

      // cnt[v] = u 和 v 的共同好友数量
      vector<int> cnt(V, 0);

      int best = 0;

      // 枚举 u -> friend -> candidate
      for (int f : g[u]) {
        for (int v : g[f]) {
          if (blocked[v])
            continue;
          cnt[v]++;
          best = max(best, cnt[v]);
        }
      }

      if (best == 0) {
        cout << "-\n";
        continue;
      }

      vector<string> ans;

      for (int v = 0; v < V; v++) {
        if (!blocked[v] && cnt[v] == best) {
          ans.push_back(name[v]);
        }
      }

      sort(ans.begin(), ans.end());
      for (int j = 0; j < (int)ans.size(); j++) {
        if (j)
          cout << ' ';
        cout << ans[j];
      }
      cout << '\n';
    }
  }
  return 0;
}
