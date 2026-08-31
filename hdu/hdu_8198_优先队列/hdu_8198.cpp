#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using int64 = long long;

using int128 = __int128_t;

void print_i128(int128 x) {
    if (x == 0) {
        cout << 0;
        return;
    }

    string s;
    while (x > 0) {
        s.push_back(char('0' + x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    
    for (int i = 1;i <= T;i++) {
        int n;
        cin >> n;

        vector<int64> a(n);
        for (int i = 0;i < n;i++) {
            cin >> a[i];
        }

        priority_queue<int128, vector<int128>, less<int128>> pq;
        for (int i = 0;i < n;i++) {
            pq.push(a[i]);
        }

        int128 ans = 0;
        while (pq.size() > 1) {
            int128 a = pq.top();
            pq.pop();
            int128 b = pq.top();
            pq.pop();
            ans += max(a, b);
            pq.push(a + b);
        }

        // 输出 int128的 ans
        print_i128(ans);
        cout << '\n';
    }
}