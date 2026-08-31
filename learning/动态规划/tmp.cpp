#include <bits/stdc++.h>
using namespace std;

class BIT {
private:
    int n;
    vector<int> tree;
public:
    BIT(int n): n(n), tree(n+1, 0) {}

    // 更新位置 x：
    // tree 中维护最大值
    void update(int x, int value) {
        while(x <= n) {
            tree[x] = max(tree[x], value);
            x += x & -x;
        }
    }

    // 查询 [1, x] 中的最大值
    int query(int x) {
        int ans = 0;
        while(x > 0) {
            ans = max(ans, tree[x]);
            x -= x & -x;
        }
        return ans;
    }
};

int LIS(const vector<int> & a) {
    int n = a.size();

    // 离散化
    vector<int> b = a;

    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());

    BIT bit(b.size());

    vector<int> dp(n);
    int ans = 0;
    for(int i = 0;i < n;i++) {
        // a[i] 的排名，从 1 开始
        int rank = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;

        // 找所有值 < a[i] 的元素中最大的 dp
        dp[i] = bit.query(rank - 1) + 1;

        // 更新当前值对应的最大 dp
        bit.update(rank, dp[i]);

        ans = max(ans, dp[i]);
    }
    return ans;
}

int main() {
    vector<int> a = {3, 1, 2, 5, 4, 7};

    cout << LIS(a) << endl;

    return 0;
}