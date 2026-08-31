#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;

    while (cin >> N >> K) {
        vector<int> vis(K + 1, 0);

        int cur = 1;      // 当前段编号
        int cnt = 0;      // 当前段出现的不同品种数
        int ans = 0;      // 已经凑齐的完整段数

        for (int i = 0; i < N; ++i) {
            int x;
            cin >> x;

            if (vis[x] != cur) {
                vis[x] = cur;
                ++cnt;
            }

            if (cnt == K) {
                ++ans;
                ++cur;
                cnt = 0;
            }
        }

        cout << ans + 1 << '\n';
    }

    return 0;
}