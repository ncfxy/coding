#include <iostream>
#include <set>
#include <vector>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<ll> x(n), y(n);
    vector<int> cnt(n, 0);

    // (当前横坐标, 云的编号)
    set<pair<ll, int>> st;

    for(int i = 0;i < n;i++) {
        cin >> x[i] >> y[i];
        st.insert({x[i], i});
    }

    for(int q = 0;q <  m;q++) {
        ll l, r, u, v;
        cin >> l >> r >> u >> v;

        vector<int> affected;

        // 找到第一片 x >= l 的云
        auto it = st.lower_bound({l, -1});

        // 先把本次受到影响的云全部取出来
        while (it != st.end() && it->first <= r) {
            affected.push_back(it->second);
            it = st.erase(it);
        }

        // 再统一进行平移
        for (int id : affected) {
            x[id] += u;
            y[id] += v;
            ++cnt[id];

            if (cnt[id] < 6) {
                st.insert({x[id], id});
            }
            // cnt == 6 时永久消失，不再插回
        }
    }

    for (int i = 0; i < n; ++i) {
        if (cnt[i] >= 6) {
            cout << "Disappeared\n";
        } else if (cnt[i] == 0) {
            cout << "Cumulus " << x[i] << ' ' << y[i] << '\n';
        } else {
            cout << "Cirrus " << x[i] << ' ' << y[i] << '\n';
        }
    }
    return 0;
}