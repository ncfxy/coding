#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while(T--) {
        int n;
        cin >> n;
        int cTotal = 0, cReward = 0;
        int sTotal = 0, sReward = 0;
        int bothTotal = 0, bothReward = 0;

        for(int i = 0;i < n;i++) {
            int c, s, r;
            cin >> c >> s >> r;
            if(c == 1) {
                cTotal++;
                if (r == 1) cReward++;
            }
            if(s == 1) {
                sTotal++;
                if (r == 1) sReward++;
            }
            if(c == 1 && s == 1) {
                bothTotal++;
                if (r == 1) bothReward++;
            }
        }

        double cProb = 0, sProb = 0, bothProb = 0;
        if (cTotal > 0) cProb = (double)cReward / cTotal;
        if (sTotal > 0) sProb = (double)sReward / sTotal;
        if (bothTotal > 0) bothProb = (double)bothReward / bothTotal;

        double result = max(cProb, max(sProb, bothProb)) * 100;
        
        // 输出保留两位小数
        cout << fixed << setprecision(2) << result << "%" << '\n';
    }
    return 0;
}