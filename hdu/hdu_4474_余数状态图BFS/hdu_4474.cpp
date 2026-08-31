#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    int kase = 0;

    while (cin >> n >> m) {
        vector<bool> forbidden(10, false);

        for (int i = 0; i < m; ++i) {
            int x;
            cin >> x;
            forbidden[x] = true;
        }

        // pre[r]：
        // -1  -> 尚未访问
        // -2  -> BFS 起点，即只有一位数字
        vector<int> pre(n, -1);
        vector<int> lastDigit(n, -1);

        queue<int> q;

        // 第一位不能为 0。
        // 从小到大加入，保证字典序最小。
        for (int d = 1; d <= 9; ++d) {
            if (forbidden[d]) continue;

            int r = d % n;

            if (pre[r] == -1) {
                pre[r] = -2;
                lastDigit[r] = d;
                q.push(r);
            }
        }

        while (!q.empty() && pre[0] == -1) {
            int r = q.front();
            q.pop();

            // 后续位可以使用 0
            for (int d = 0; d <= 9; ++d) {
                if (forbidden[d]) continue;

                int nr = (r * 10 + d) % n;

                if (pre[nr] != -1)
                    continue;

                pre[nr] = r;
                lastDigit[nr] = d;
                q.push(nr);

                if (nr == 0)
                    break;
            }
        }

        cout << "Case " << ++kase << ": ";

        if (pre[0] == -1) {
            cout << -1 << '\n';
            continue;
        }

        // 从余数 0 反向恢复数字
        string ans;

        int cur = 0;
        while (cur != -2) {
            ans.push_back(char('0' + lastDigit[cur]));
            cur = pre[cur];
        }

        reverse(ans.begin(), ans.end());

        cout << ans << '\n';
    }

    return 0;
}