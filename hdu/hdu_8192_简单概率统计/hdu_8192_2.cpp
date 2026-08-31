#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    cout << fixed << setprecision(2);

    while (T--) {
        int n;
        cin >> n;

        int cntA = 0, winA = 0;
        int cntB = 0, winB = 0;
        int cntAB = 0, winAB = 0;

        for (int i = 0; i < n; ++i) {
            int a, b, c;
            cin >> a >> b >> c;

            if (a) {
                ++cntA;
                winA += c;
            }

            if (b) {
                ++cntB;
                winB += c;
            }

            if (a && b) {
                ++cntAB;
                winAB += c;
            }
        }

        long double ans = 0;

        if (cntA > 0) {
            ans = max(ans, (long double)winA / cntA);
        }

        if (cntB > 0) {
            ans = max(ans, (long double)winB / cntB);
        }

        if (cntAB > 0) {
            ans = max(ans, (long double)winAB / cntAB);
        }

        cout << ans * 100 << "%\n";
    }

    return 0;
}