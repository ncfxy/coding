
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 2005;
const int LOG = 12;   // 2^11 > 2000

int n, k;
int a[MAXN];

// to[j][i]   : 从 i 开始进行 2^j 局后的下一张牌
// gain[j][i] : 这 2^j 局玩家赢的次数
// lastPos[j][i] : 这 2^j 局中最后一局的开始位置
int toPos[LOG][MAXN];
int gainWin[LOG][MAXN];
int lastPos[LOG][MAXN];

struct RoundResult {
    bool ok;
    int nxt;
    int win;
};

/*
 * 在原数组中从 start 开始模拟一局。
 *
 * 如果这一局需要访问 n 之后的牌，则 ok=false。
 *
 * nxt 表示下一张未使用牌的位置，允许为 n+1。
 */
RoundResult simulateOriginal(int start) {
    int idx = start;

    // 初始至少需要 4 张
    if (idx + 3 > n) {
        return {false, 0, 0};
    }

    int player = a[idx] + a[idx + 2];
    int dealer = a[idx + 1] + a[idx + 3];

    idx += 4;

    // 玩家
    int hit = 0;

    while (player <= 15 && hit < 3) {
        if (idx > n) {
            return {false, 0, 0};
        }

        player += a[idx++];
        ++hit;

        // 爆牌优先
        if (player > 21) {
            return {true, idx, 0};
        }

        // 成功拿满三张额外牌
        if (hit == 3) {
            return {true, idx, 1};
        }
    }

    // 庄家
    hit = 0;

    while (dealer <= 15 && hit < 3) {
        if (idx > n) {
            return {false, 0, 0};
        }

        dealer += a[idx++];
        ++hit;

        if (dealer > 21) {
            return {true, idx, 1};
        }

        if (hit == 3) {
            return {true, idx, 0};
        }
    }

    // 比较点数
    return {true, idx, player > dealer ? 1 : 0};
}

/*
 * 对给定切法 (p,q)，从新牌堆位置 t 开始模拟一局。
 *
 * 调用时一定有 t <= n-k+1，并且 k>=10，
 * 所以保证至少还有 10 张牌，不需要做越界判断。
 */
pair<int, int> simulateCutRound(int t, int p, int q) {
    int L = q - p + 1;

    auto getCard = [&](int pos) -> int {
        int id;

        if (pos <= L) {
            // [p,q]
            id = p + pos - 1;
        } else if (pos <= q) {
            // [1,p-1]
            id = pos - L;
        } else {
            // [q+1,n]
            id = pos;
        }

        return a[id];
    };

    int idx = t;

    int player = getCard(idx) + getCard(idx + 2);
    int dealer = getCard(idx + 1) + getCard(idx + 3);

    idx += 4;

    // 玩家
    int hit = 0;

    while (player <= 15 && hit < 3) {
        player += getCard(idx++);
        ++hit;

        if (player > 21) {
            return {idx, 0};
        }

        if (hit == 3) {
            return {idx, 1};
        }
    }

    // 庄家
    hit = 0;

    while (dealer <= 15 && hit < 3) {
        dealer += getCard(idx++);
        ++hit;

        if (dealer > 21) {
            return {idx, 1};
        }

        if (hit == 3) {
            return {idx, 0};
        }
    }

    return {idx, player > dealer ? 1 : 0};
}

void buildDoubling() {
    memset(toPos, 0, sizeof(toPos));
    memset(gainWin, 0, sizeof(gainWin));
    memset(lastPos, 0, sizeof(lastPos));

    // 一局
    for (int i = 1; i <= n; ++i) {
        RoundResult res = simulateOriginal(i);

        if (res.ok) {
            toPos[0][i] = res.nxt;
            gainWin[0][i] = res.win;
            lastPos[0][i] = i;
        }
    }

    // 倍增
    for (int j = 1; j < LOG; ++j) {
        for (int i = 1; i <= n; ++i) {
            int mid = toPos[j - 1][i];

            // mid==n+1 时已经没有下一局可以继续
            if (mid >= 1 && mid <= n &&
                toPos[j - 1][mid] != 0) {

                toPos[j][i] =
                    toPos[j - 1][mid];

                gainWin[j][i] =
                    gainWin[j - 1][i]
                    + gainWin[j - 1][mid];

                // 最后一局在后一半
                lastPos[j][i] =
                    lastPos[j - 1][mid];
            }
        }
    }
}

/*
 * 计算固定切法 (p,q) 能赢多少局。
 */
int solveCut(int p, int q) {
    int L = q - p + 1;

    // 新牌堆中，允许开始一局的最大位置
    int M = n - k + 1;

    // 当前新牌堆位置
    int t = 1;

    int answer = 0;

    while (t <= M) {
        int pos;        // 当前位置对应的原数组位置
        int r;          // 当前连续段在原数组中的右端点
        int offset;     // 新位置 = 原位置 + offset

        if (t <= L) {
            // 第一段 [p,q]
            pos = p + t - 1;
            r = q;
            offset = t - pos;       // = 1-p
        } else if (t <= q) {
            // 第二段 [1,p-1]
            pos = t - L;
            r = p - 1;
            offset = t - pos;       // = L
        } else {
            // 第三段 [q+1,n]
            pos = t;
            r = n;
            offset = 0;
        }

        int oldPos = pos;

        /*
         * 尽可能使用原数组上的倍增转移。
         */
        for (int j = LOG - 1; j >= 0; --j) {
            if (pos > r) break;

            if (toPos[j][pos] == 0)
                continue;

            /*
             * 条件1：
             * 这 2^j 局全部不能越过当前连续段。
             */
            if (toPos[j][pos] > r + 1)
                continue;

            /*
             * 条件2：
             * 最后一局在新牌堆中的开始位置 <= M。
             */
            if (lastPos[j][pos] + offset > M)
                continue;

            answer += gainWin[j][pos];
            pos = toPos[j][pos];
        }

        /*
         * 成功跳过了至少一局。
         *
         * 原位置增加多少，新牌堆位置也增加多少，
         * 因为在一个连续段内两者只差常数。
         */
        if (pos != oldPos) {
            t += pos - oldPos;
            continue;
        }

        /*
         * t<=M，但在当前连续段连一局都走不了：
         * 下一局一定会跨拼接边界。
         *
         * 直接按照切牌后的真实顺序模拟。
         */
        auto res = simulateCutRound(t, p, q);

        t = res.first;
        answer += res.second;
    }

    return answer;
}

int cardValue(char c) {
    if (c == 'A')
        return 1;

    if (c >= '2' && c <= '9')
        return c - '0';

    // T, J, Q, K
    return 10;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc = 0;

    while (cin >> n >> k) {
        for (int i = 1; i <= n; ++i) {
            char c;
            cin >> c;
            a[i] = cardValue(c);
        }

        buildDoubling();

        int ans = 0;

        /*
         * 1 < p <= q < n
         */
        for (int p = 2; p <= n - 1; ++p) {
            for (int q = p; q <= n - 1; ++q) {
                ans = max(ans, solveCut(p, q));
            }
        }

        cout << "Case " << ++tc << ": " << ans << '\n';
    }

    return 0;
}