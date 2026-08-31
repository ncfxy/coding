#include <iostream>

using namespace std;

using int64 = long long;

const int MAXN = 1000;
const int64 MOD = 1000000007LL;

int64 dp[MAXN + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // dp[n] = sum(dp[d]), d | (n - 1)
    dp[1] = 1;

    for (int n = 2; n <= MAXN; n++) {
        int x = n - 1;
        int64 ans = 0;

        for(int d = 1; 1LL * d * d <= x;d++) {
            if (x % d != 0) continue;

            // d 是一个约数的话
            ans += dp[d];
            if(ans >= MOD) {
                ans -= MOD;
            }

            // x / d 是另一个约数
            int other = x / d;
            if(other != d) {
                ans += dp[other];
                if(ans >= MOD) {
                    ans -= MOD;
                }
            }
        }
        dp[n] = ans;
    }

    int n;
    int cas = 0;

    while(cin >> n) {
        cout << "Case " << ++cas << ": " << dp[n] << endl;
    }

    return 0;
}