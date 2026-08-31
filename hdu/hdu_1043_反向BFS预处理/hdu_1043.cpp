#include <iostream>
#include <string>
#include <queue>
using namespace std;

const int MAXS = 362880;

int fac[10];

bool vis[MAXS];
string answer[MAXS];

struct Node {
    string s;
    string path;
};

// 康托展开
int cantor(const string& s) {
    int a[9];

    for (int i = 0; i < 9; ++i) {
        if (s[i] == 'x')
            a[i] = 9;
        else
            a[i] = s[i] - '0';
    }

    int rank = 0;

    for (int i = 0; i < 9; ++i) {
        int cnt = 0;

        for (int j = i + 1; j < 9; ++j) {
            if (a[j] < a[i])
                ++cnt;
        }

        rank += cnt * fac[8 - i];
    }

    return rank;
}

void init() {
    fac[0] = 1;
    for (int i = 1; i <= 9; ++i)
        fac[i] = fac[i - 1] * i;

    queue<Node> q;

    string goal = "12345678x";

    int goalRank = cantor(goal);
    vis[goalRank] = true;
    answer[goalRank] = "";

    q.push({goal, ""});

    // BFS 时 x 的移动方向
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    // BFS 从 goal 反向扩展。
    // 新状态回到当前状态时所需要的方向。
    char revMove[4] = {
        'd', // BFS: u
        'u', // BFS: d
        'r', // BFS: l
        'l'  // BFS: r
    };

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        int p = cur.s.find('x');

        int x = p / 3;
        int y = p % 3;

        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3)
                continue;

            int np = nx * 3 + ny;

            string nxt = cur.s;
            swap(nxt[p], nxt[np]);

            int id = cantor(nxt);

            if (vis[id])
                continue;

            vis[id] = true;

            // 从 nxt 到 goal：
            // 先走一步回到 cur，再按照 cur.path 走
            string nxtPath;
            nxtPath += revMove[k];
            nxtPath += cur.path;

            answer[id] = nxtPath;

            q.push({nxt, nxtPath});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();

    while (true) {
        vector<char> a(9);

        if (!(cin >> a[0]))
            break;

        for (int i = 1; i < 9; ++i)
            cin >> a[i];

        string s;
        for (char c : a)
            s += c;

        int id = cantor(s);

        if (!vis[id]) {
            cout << "unsolvable\n";
        } else {
            cout << answer[id] << '\n';
        }
    }

    return 0;
}