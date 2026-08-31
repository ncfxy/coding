#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc = 1;
    int n;
    while (cin >> n) {
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            
            // 求 s 的 ASCII码和 
            int sum = 0;
            for (char c : s) {
                sum += c;
            }
            if (sum > ans) {
                ans = sum;
            }
        }
        cout << "Case " << tc << ": " << ans << endl;
        ++tc;
    }
    return 0;
}