#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

using int64 = long long;
using uint64 = unsigned long long;

static const int MOD1 = 1000000007;
static const int MOD2 = 1000000009;
static const int BASE = 911382323;

struct Node {
    int h1 = 0;
    int h2 = 0;
    int len = 0;
};

struct Key {
    int len;
    int h1;
    int h2;

    bool operator==(const Key& other) const {
        return len == other.len &&
               h1 == other.h1 &&
               h2 == other.h2;
    }
};

struct KeyHasher {
    static uint64 splitmix64(uint64 x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }

    size_t operator()(const Key& k) const {
        uint64 x = ((uint64)(unsigned int)k.h1 << 32)
                 | (unsigned int)k.h2;

        x ^= (uint64)k.len * 0x9e3779b97f4a7c15ULL;

        return splitmix64(x);
    }
};

class SegmentTree {
private:
    int n;
    vector<Node> tr;
    vector<int> pw1, pw2;
    string s;

    Node mergeNode(const Node& a, const Node& b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;

        res.len = a.len + b.len;

        res.h1 = (
            (int64)a.h1 * pw1[b.len] + b.h1
        ) % MOD1;

        res.h2 = (
            (int64)a.h2 * pw2[b.len] + b.h2
        ) % MOD2;

        return res;
    }

    void build(int p, int l, int r) {
        if (l == r) {
            int v = s[l] - 'a' + 1;

            tr[p].h1 = v;
            tr[p].h2 = v;
            tr[p].len = 1;

            return;
        }

        int mid = (l + r) >> 1;

        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);

        tr[p] = mergeNode(
            tr[p << 1],
            tr[p << 1 | 1]
        );
    }

    void update(
        int p,
        int l,
        int r,
        int pos,
        char c
    ) {
        if (l == r) {
            int v = c - 'a' + 1;

            tr[p].h1 = v;
            tr[p].h2 = v;

            return;
        }

        int mid = (l + r) >> 1;

        if (pos <= mid) {
            update(
                p << 1,
                l,
                mid,
                pos,
                c
            );
        } else {
            update(
                p << 1 | 1,
                mid + 1,
                r,
                pos,
                c
            );
        }

        tr[p] = mergeNode(
            tr[p << 1],
            tr[p << 1 | 1]
        );
    }

    Node query(
        int p,
        int l,
        int r,
        int ql,
        int qr
    ) {
        if (ql <= l && r <= qr) {
            return tr[p];
        }

        int mid = (l + r) >> 1;

        if (qr <= mid) {
            return query(
                p << 1,
                l,
                mid,
                ql,
                qr
            );
        }

        if (ql > mid) {
            return query(
                p << 1 | 1,
                mid + 1,
                r,
                ql,
                qr
            );
        }

        // 注意：
        // 必须先左边，再右边
        Node left = query(
            p << 1,
            l,
            mid,
            ql,
            qr
        );

        Node right = query(
            p << 1 | 1,
            mid + 1,
            r,
            ql,
            qr
        );

        return mergeNode(left, right);
    }

public:
    SegmentTree(const string& str) {
        s = str;
        n = (int)s.size();

        tr.resize(n * 4 + 5);

        pw1.resize(n + 1);
        pw2.resize(n + 1);

        pw1[0] = pw2[0] = 1;

        for (int i = 1; i <= n; ++i) {
            pw1[i] = (int64)pw1[i - 1] * BASE % MOD1;
            pw2[i] = (int64)pw2[i - 1] * BASE % MOD2;
        }

        build(1, 0, n - 1);
    }

    void change(int pos, char c) {
        update(
            1,
            0,
            n - 1,
            pos,
            c
        );
    }

    Node getHash(int l, int r) {
        return query(
            1,
            0,
            n - 1,
            l,
            r
        );
    }
};

Key getWordHash(const string& s) {
    int h1 = 0;
    int h2 = 0;

    for (char c : s) {
        int v = c - 'a' + 1;

        h1 = (
            (int64)h1 * BASE + v
        ) % MOD1;

        h2 = (
            (int64)h2 * BASE + v
        ) % MOD2;
    }

    return {
        (int)s.size(),
        h1,
        h2
    };
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; ++tc) {
        int n;
        cin >> n;

        unordered_set<Key, KeyHasher> dict;

        // 避免频繁 rehash
        dict.reserve(n * 2 + 10);
        dict.max_load_factor(0.7);

        for (int i = 0; i < n; ++i) {
            string w;
            cin >> w;

            dict.insert(getWordHash(w));
        }

        string S;
        cin >> S;

        SegmentTree seg(S);

        int m;
        cin >> m;

        cout << "Case #" << tc << ":\n";

        while (m--) {
            char op;
            cin >> op;

            if (op == 'Q') {
                int L, R;
                cin >> L >> R;

                Node cur = seg.getHash(L, R);

                Key key{
                    cur.len,
                    cur.h1,
                    cur.h2
                };

                if (dict.find(key) != dict.end()) {
                    cout << "Yes\n";
                } else {
                    cout << "No\n";
                }
            } else {
                int X;
                char Y;

                cin >> X >> Y;

                seg.change(X, Y);
            }
        }
    }

    return 0;
}