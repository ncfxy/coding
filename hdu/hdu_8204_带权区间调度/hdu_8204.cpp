#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Segment {
    int l, r;
    long long w;

    bool operator<(const Segment& other) const {
        return r < other.r;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int L, n, m;
        cin >> L >> n >> m;

        vector<pair<int, int>> input(n);
        for (int i = 0; i < n; ++i) {
            cin >> input[i].first >> input[i].second;
        }
        
        vector<int> appear(m);
        for (int i = 0; i < m; ++i) {
            cin >> appear[i];
        }
        sort(appear.begin(), appear.end());

        vector<Segment> segs;
        segs.reserve(n);

        // 仅保留至少包含一次男明星出现时刻的片段
        for (int i = 0; i < n; ++i) {
            int l = input[i].first, r = input[i].second;
            auto it = lower_bound(appear.begin(), appear.end(), l);
            if (it != appear.end() && *it <= r) {
                segs.push_back({l, r, r - l + 1});
            }
        }

        // 默认排序: 右端点升序
        sort(segs.begin(), segs.end());

        int k = segs.size();
        vector<int> ends(k + 1);
        for (int i = 1; i <= k; ++i) {
            ends[i] = segs[i - 1].r;
        }

        // dp[i]：考虑排序后前 i 个片段时，最多可观看分钟数
        vector<long long> dp(k + 1, 0);
        for (int i = 1; i <= k; ++i) {
            int l = segs[i - 1].l;

            // 找到右端点严格小于 l 的最后一个片段数
            // lower_bound 返回第一个 >= l 的位置，因此其下标就是可兼容片段个数
            int p = lower_bound(ends.begin(), ends.begin() + i, l) - ends.begin();
            dp[i] = max(dp[i - 1], dp[p-1] + segs[i - 1].w);
        }

        cout << dp[k] << '\n';
    }

    return 0;
}