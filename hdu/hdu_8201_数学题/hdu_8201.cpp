#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        long long a, b, n, m;
        cin >> a >> b >> n >> m;

        long long k = n / m;
        long long need = k * k;

        cout << (min(a, b) >= need ? "YES\n" : "NO\n");
    }

    return 0;
}