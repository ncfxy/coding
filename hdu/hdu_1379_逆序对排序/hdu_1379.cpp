#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct DNA {
    string s;
    int inv;
    int id;
};

int getId(char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    return 3; // T
}

// 计算字符串的逆序对数量
int getInversions(const string& s) {
    int cnt[4] = {0, 0, 0, 0};
    int ans = 0;

    for (char c : s) {
        int x = getId(c);

        // 左边所有比当前字符大的字符都会形成逆序对
        for (int j = x + 1; j < 4; ++j) {
            ans += cnt[j];
        }

        ++cnt[x];
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 0; tc < T; ++tc) {
        int n, m;
        cin >> n >> m;

        vector<DNA> a(m);

        for (int i = 0; i < m; ++i) {
            cin >> a[i].s;
            a[i].inv = getInversions(a[i].s);
            a[i].id = i;
        }

        sort(a.begin(), a.end(), [](const DNA& x, const DNA& y) {
            if (x.inv != y.inv)
                return x.inv < y.inv;
            return x.id < y.id;
        });

        if (tc > 0)
            cout << '\n';

        for (const auto& dna : a) {
            cout << dna.s << '\n';
        }
    }

    return 0;
}