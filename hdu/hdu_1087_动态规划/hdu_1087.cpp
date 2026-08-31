#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while(cin >> n && n != 0) {

        vector<int> a(n);
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        vector<int> dp(n, 0);
        dp[0] = a[0];
        int ans = dp[0];

        for(int i = 1; i < n; ++i) {
            dp[i] = a[i];
            for(int j = 0; j < i; ++j) {
                if(a[j] < a[i]) {
                    dp[i] = max(dp[i], dp[j] + a[i]);
                }
            }
            if (dp[i] > ans) ans = dp[i];
        }

        cout << ans << '\n';
    }

    return 0;
}