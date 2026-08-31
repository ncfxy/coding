

#include <iostream>
#include <cmath>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

const int MAXN = 100000 + 5;

struct Node {
    int64 sum;
    int64 mx;
} tr[MAXN << 2];

int64 a[MAXN];

long long isqrt(long long x) {
    long long r = sqrtl((long double)x);

    // 防止浮点精度误差
    while ((i128)(r + 1) * (r + 1) <= x)
        ++r;

    while ((i128)r * r > x)
        --r;

    return r;
}

void pushUp(int p) {
    tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
    tr[p].mx = max(tr[p << 1].mx, tr[p << 1 | 1].mx);
}

void build(int p, int l, int r) {
    if (l == r) {
        tr[p].sum = tr[p].mx = a[l];
        return;
    }

    int mid = (l + r) >> 1;

    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);

    pushUp(p);
}

void update(int p, int l, int r, int ql, int qr) {
    // 当前区间全部都是 0 或 1，再开方不会发生任何变化
    if (tr[p].mx <= 1)
        return;

    if (l == r) {
        tr[p].sum = tr[p].mx = isqrt(tr[p].sum);
        return;
    }

    int mid = (l + r) >> 1;

    if (ql <= mid)
        update(p << 1, l, mid, ql, qr);

    if (qr > mid)
        update(p << 1 | 1, mid + 1, r, ql, qr);

    pushUp(p);
}

long long query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return tr[p].sum;

    int mid = (l + r) >> 1;
    long long ans = 0;

    if (ql <= mid)
        ans += query(p << 1, l, mid, ql, qr);

    if (qr > mid)
        ans += query(p << 1 | 1, mid + 1, r, ql, qr);

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int kase = 0;

    while (cin >> n) {
        for (int i = 1; i <= n; ++i)
            cin >> a[i];

        build(1, 1, n);

        int m;
        cin >> m;

        cout << "Case #" << ++kase << ":\n";

        while (m--) {
            int t, x, y;
            cin >> t >> x >> y;

            // 题目不保证 x <= y
            if (x > y)
                swap(x, y);

            if (t == 0) {
                update(1, 1, n, x, y);
            } else {
                cout << query(1, 1, n, x, y) << '\n';
            }
        }

        cout << '\n';
    }

    return 0;
}