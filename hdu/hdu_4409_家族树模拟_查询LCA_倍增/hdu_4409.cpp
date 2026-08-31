#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

static const int MAXN = 30005;
static const int LOG = 16; // 下标 0..15，2^15 = 32768

string nameOf[MAXN];
vector<int> child[MAXN];

int father[MAXN];
int depthArr[MAXN];
int up[MAXN][LOG];

unordered_map<string, int> id;

/*
 * 普通 LCA：
 * 注意这里允许返回 u/v 自己，
 * 严格祖先的特殊处理放到查询 c 中。
 */
int lca(int u, int v) {
    if (depthArr[u] < depthArr[v]) {
        swap(u, v);
    }

    // 先把 u 提到与 v 相同深度
    int diff = depthArr[u] - depthArr[v];

    for (int j = 0; j < LOG; ++j) {
        if (diff & (1 << j)) {
            u = up[u][j];
        }
    }

    if (u == v) {
        return u;
    }

    // 一起向上跳
    for (int j = LOG - 1; j >= 0; --j) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }

    return up[u][0];
}

/*
 * 输出排序后的家谱。
 * 使用非递归 DFS，避免极端链状家谱导致栈溢出。
 */
void printFamily(int root) {
    vector<int> st;
    st.reserve(30000);

    st.push_back(root);

    while (!st.empty()) {
        int u = st.back();
        st.pop_back();

        for (int i = 0; i < depthArr[u]; ++i) {
            cout << '.';
        }
        cout << nameOf[u] << '\n';

        /*
         * child[u] 已经是升序。
         * 栈是后进先出，所以倒着压入。
         */
        for (int i = (int)child[u].size() - 1; i >= 0; --i) {
            st.push_back(child[u][i]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;

    while (cin >> N && N) {

        /*
         * 清空上一组数据。
         *
         * 注意：
         * 上一组 N 可能比当前 N 大，因此不能只清当前 N 个。
         *
         * 不过实际只有当前新建节点会使用 child，
         * 我们在读入节点时逐个 clear 最安全。
         */
        id.clear();
        id.reserve(N * 2 + 10);
        id.max_load_factor(0.7);

        string s;

        /*
         * 根节点 Mr. X
         */
        cin >> s;

        child[0].clear();

        nameOf[0] = s;
        id[s] = 0;

        father[0] = 0;
        depthArr[0] = 0;

        for (int j = 0; j < LOG; ++j) {
            up[0][j] = 0;
        }

        /*
         * last[d]：
         * 当前输入位置之前最后出现的深度 d 节点。
         */
        vector<int> last(N + 1, -1);
        last[0] = 0;

        for (int i = 1; i < N; ++i) {
            child[i].clear();

            cin >> s;

            int d = 0;
            while (d < (int)s.size() && s[d] == '.') {
                ++d;
            }

            string nm = s.substr(d);

            nameOf[i] = nm;
            id[nm] = i;

            depthArr[i] = d;

            /*
             * 根据题意：
             * 当前人的父亲是最近的深度 d-1 的节点。
             */
            int p = last[d - 1];

            father[i] = p;
            child[p].push_back(i);

            last[d] = i;

            /*
             * 倍增祖先表
             */
            up[i][0] = p;

            for (int j = 1; j < LOG; ++j) {
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }

        /*
         * 每个父亲的孩子按姓名字典序排序。
         */
        for (int u = 0; u < N; ++u) {
            sort(child[u].begin(), child[u].end(),
                 [&](int a, int b) {
                     return nameOf[a] < nameOf[b];
                 });
        }

        int Q;
        cin >> Q;

        while (Q--) {
            char op;
            cin >> op;

            if (op == 'L') {

                printFamily(0);

            } else if (op == 'b') {

                string nm;
                cin >> nm;

                int u = id[nm];

                /*
                 * Mr. X 没有父亲。
                 * 根据该题定义，它的 brothers 数量为 1。
                 */
                if (u == 0) {
                    cout << 1 << '\n';
                } else {
                    cout << child[father[u]].size() << '\n';
                }

            } else if (op == 'c') {

                string a, b;
                cin >> a >> b;

                int u = id[a];
                int v = id[b];

                int w = lca(u, v);

                /*
                 * ★ 本题最重要的坑 ★
                 *
                 * ancestor 是严格祖先。
                 * 如果普通 LCA 正好是查询节点之一，
                 * 那么它自己不能算自己的 ancestor，
                 * 必须再往上走一层。
                 */
                if (w == u || w == v) {
                    w = father[w];
                }

                cout << nameOf[w] << '\n';
            }
        }
    }

    return 0;
}