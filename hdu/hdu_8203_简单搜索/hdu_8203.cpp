#include <iostream>
#include <vector>

using namespace std;

bool win(const bool a[4][4]) {
    // 判断是否在同一行或同一列
    for (int i = 1;i <= 3; i++) {
        if (a[i][1] && a[i][2] && a[i][3]) return true;
        if (a[1][i] && a[2][i] && a[3][i]) return true;
    }

    // 判断是否在一条对角线
    return (a[1][1] && a[2][2] && a[3][3]) ||
           (a[1][3] && a[2][2] && a[3][1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;

        vector<pair<int, int>> me(n), opponent(n);
        bool occupied[4][4] = {};

        for (int i = 0;i < n; i++) {
            cin >> me[i].first >> me[i].second;
            occupied[me[i].first][me[i].second] = true;
        }

        for (int i = 0;i < n; i++) {
            cin >> opponent[i].first >> opponent[i].second;
            occupied[opponent[i].first][opponent[i].second] = true;
        }

        bool found = false;

        // 按行、列升序枚举，首次找到的就是字典序最小答案
        for (int r = 1; r <= 3 && !found; r++) {
            for (int c = 1; c <= 3 && !found; c++) {
                if (occupied[r][c]) continue;

                bool board[4][4] = {};

                // n = 3 时，me[0] 会消失；否则所有己方棋子保留
                // n = 3 时，me[0] 会消失；否则所有己方棋子保留
                int start = (n == 3 ? 1 : 0);
                for (int i = start; i < n; i++) {
                    board[me[i].first][me[i].second] = true;
                }

                board[r][c] = true;

                if (win(board)) {
                    cout << r << ' ' << c << '\n';
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "Columbina Hyposelenia\n";
        }
    }

    return 0;
}