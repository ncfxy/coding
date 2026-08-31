#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;

        int cnt1 = 0;
        int cntBig = 0;
        long long sumBig = 0;

        for(int i = 0;i < n;i++) {
            int x;
            cin >> x;

            if(x == 1) {
                cnt1++;
            } else {
                cntBig++;
                sumBig += x;
            }
        }

        bool bobWin = false;

        // 特殊情况1: 全部都是1
        if(cntBig == 0) {
            bobWin = (cnt1 % 3 == 0);
        }

        // 特殊情况2: 一个2 + 若干个1
        else if(cntBig == 1 && sumBig == 2) {
            bobWin = (cnt1 % 3 == 0);
        }
        // 一般情况
        else {
            bobWin = (cnt1 % 2 == 0) && ((sumBig + cntBig -1) % 2 == 0);
        }
        cout << "Case #" << t << ": "
             << (bobWin ? "Bob" : "Alice") << '\n';
    }
}