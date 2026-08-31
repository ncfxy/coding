#include <iostream>
#include <vector>

using namespace std;
using int64 = long long;

const int MAXM = 20;

int64 cnt[MAXM + 1];
int64 startPos[MAXM + 1];
int64 pairCnt[MAXM + 1];

/*
    build(sz, rank)

    返回：
    节点数恰好为 sz 的所有树中，
    按题目规定排序后的第 rank 棵树。
    
    rank 从 0 开始。
*/
string buildTree(int sz, int64 rank) {
    if(sz == 0) return "";

    // 当前根占1个节点
    int total = sz - 1;

    /*
        首先确定左子树。

        左子树大小为 a 时：
        中 + 右共有 total-a 个节点。

        对于一棵固定的左子树，
        中右组合数为 pairCnt[total-a]。
    */
    for (int a = 0; a <= total; ++a) {
        int t = total - a;

        int64 waysPerLeft = pairCnt[t];
        int64 block = cnt[a] * waysPerLeft;

        if (rank >= block) {
            rank -= block;
            continue;
        }

        // 已确定左子树大小为 a
        int64 rankL = rank / waysPerLeft;
        rank %= waysPerLeft;

        /*
            再确定中子树大小 b。
            右子树大小 c = t-b。

            对于一棵固定的中子树，
            有 cnt[c] 种右子树。
        */
        for (int b = 0; b <= t; ++b) {
            int c = t - b;

            int64 waysPerMid = cnt[c];
            int64 block2 = cnt[b] * waysPerMid;

            if (rank >= block2) {
                rank -= block2;
                continue;
            }

            int64 rankM = rank / waysPerMid;
            int64 rankR = rank % waysPerMid;

            string L = buildTree(a, rankL);
            string M = buildTree(b, rankM);
            string R = buildTree(c, rankR);

            string ans;

            // 空子树直接跳过
            if (a > 0) {
                ans += "(" + L + ")";
            }

            if (b > 0) {
                ans += "(" + M + ")";
            }

            if (c > 0) {
                ans += "(" + R + ")";
            }

            ans += 'X';
            
            return ans;
        }
    }
    // 理论上不会到这里
    return "";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    /*
        cnt[m]：
        恰好 m 个节点的三叉有序树数量。

        cnt[0] = 1，表示空树。
    */
    cnt[0] = 1;

    for (int m = 1; m <= MAXM; ++m) {
        cnt[m] = 0;

        for (int a = 0; a <= m - 1; ++a) {
            for (int b = 0; b <= m - 1 - a; ++b) {
                int c = m - 1 - a - b;

                cnt[m] += cnt[a] * cnt[b] * cnt[c];
            }
        }
    }

    /*
        pairCnt[t]：
        两棵有序子树总节点数恰好为 t 时，
        一共有多少种组合。
    */
    for (int t = 0; t <= MAXM; ++t) {
        pairCnt[t] = 0;

        for (int b = 0; b <= t; ++b) {
            pairCnt[t] += cnt[b] * cnt[t - b];
        }
    }

    /*
        startPos[m]：
        m 个节点的树的第一个全局编号。

        因为空树编号 0，
        所以：
            startPos[1] = 1
            startPos[2] = 2
            startPos[3] = 5
            ...
    */
    int64 sum = 0;

    for (int m = 0; m <= MAXM; ++m) {
        startPos[m] = sum;
        sum += cnt[m];
    }

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; ++tc) {
        int64 n;
        cin >> n;

        // 找到 n 属于哪个节点数层
        int sz = 1;

        while (!(startPos[sz] <= n &&
                 n < startPos[sz] + cnt[sz])) {
            ++sz;
        }

        // 转换成这一层内部的 0-based 排名
        int64 rank = n - startPos[sz];

        cout << "Case #" << tc << ": "
             << buildTree(sz, rank) << '\n';
    }
    return 0;
}