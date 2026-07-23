#include <cstring>
#include <iostream>

using namespace std;

const long long MOD = 998244353;
// 模意义下 2 的逆元：因为 MOD 为奇数，(MOD+1)/2 即为 2^{-1}
// 用于计算 C(len, 2) = len*(len-1)/2
const long long INV2 = (MOD + 1) / 2;

const int MAXN = 2e6 + 5;

// ========== 线段树节点信息 ==========
// 下标从 1 开始；节点 node 的左右儿子为 node*2、node*2+1
//
// sum[node]  : 该节点对应区间内所有数的和
// mul[node]  : 该节点对应区间内所有「无序数对」的乘积之和
//              即 sum_{i < j, i,j 在区间内} a[i] * a[j]
// lazy[node] : 懒标记，表示该区间内每个数还需要统一加上的值
//              （节点自身的 sum/mul 已经包含了这个加数的影响，
//               但尚未下推到子孙节点）
long long sum[4 * MAXN];
long long mul[4 * MAXN];
long long lazy[4 * MAXN];
long long a[MAXN]; // 原始数组，下标 1..n

// 由左右儿子信息合并得到当前节点信息
// 设左区间和为 SL、乘积和为 ML，右区间和为 SR、乘积和为 MR
// 则：
//   总和   S  = SL + SR
//   乘积和 M  = ML + MR + SL * SR
// 其中 SL*SR 对应所有「一个在左区间、一个在右区间」的数对乘积之和
void pushup(int node) {
    sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
    mul[node] = (mul[node * 2] + mul[node * 2 + 1] +
                 sum[node * 2] * sum[node * 2 + 1] % MOD) % MOD;
}

// 将当前节点对应区间 [l, r] 内每个数加上 x
// 同时更新本节点的 sum、mul，并把加数累加到本节点的 lazy
//
// 推导（设区间长度为 len，旧和为 S，旧乘积和为 M）：
//   每个 a_i 变为 a_i + x 后：
//   M' = sum_{i<j} (a_i+x)(a_j+x)
//      = sum_{i<j} (a_i a_j + x(a_i+a_j) + x^2)
//      = M + x * sum_{i<j}(a_i+a_j) + x^2 * C(len, 2)
//
//   而 sum_{i<j}(a_i+a_j) = 每个 a_i 在数对中出现 (len-1) 次
//                        = (len-1) * S
//   C(len, 2) = len*(len-1)/2
//
//   因此：M' = M + x*(len-1)*S + x^2*len*(len-1)/2
//         S' = S + x*len
void apply(int node, int l, int r, long long x) {
    x %= MOD;
    if (x < 0) x += MOD;
    int len = r - l + 1;
    long long old_sum = sum[node];

    // 叶子节点只有一个数，不存在数对，mul 恒为 0
    if (len > 1) {
        mul[node] = (mul[node] + x * (len - 1) % MOD * old_sum % MOD +
                     x * x % MOD * len % MOD * (len - 1) % MOD * INV2 % MOD) %
                    MOD;
    }
    sum[node] = (sum[node] + x * len % MOD) % MOD;
    // 标记挂在本节点上，等需要访问儿子时再 pushdown
    lazy[node] = (lazy[node] + x) % MOD;
}

// 将本节点的懒标记下推给左右儿子
// 注意：apply 会立刻修正儿子的 sum/mul，并在儿子上继续挂 lazy
void pushdown(int node, int l, int r) {
    if (lazy[node] == 0 || l == r) return; // 无标记，或已是叶子
    int mid = (l + r) / 2;
    apply(node * 2, l, mid, lazy[node]);
    apply(node * 2 + 1, mid + 1, r, lazy[node]);
    lazy[node] = 0; // 本节点标记已下传，清空
}

// 建树：递归构建 [l, r]，对应节点编号 node
void build(int l, int r, int node) {
    lazy[node] = 0;
    if (l == r) {
        sum[node] = a[l] % MOD;
        mul[node] = 0; // 单点没有数对
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2);
    build(mid + 1, r, node * 2 + 1);
    pushup(node);
}

// 查询区间 [ql, qr] 的 (sum, mul)
// 返回值：first = 区间和，second = 区间乘积和
pair<long long, long long> query(int l, int r, int node, int ql, int qr) {
    // 当前节点被询问区间完全覆盖，直接返回节点信息
    // （节点信息已包含自身 lazy 的影响，无需再处理）
    if (ql <= l && qr >= r) {
        return {sum[node], mul[node]};
    }

    // 要访问儿子，必须先把懒标记下推，保证儿子信息是最新的
    pushdown(node, l, r);

    int mid = (l + r) / 2;
    pair<long long, long long> left = {0, 0};
    pair<long long, long long> right = {0, 0};
    if (ql <= mid) {
        left = query(l, mid, node * 2, ql, qr);
    }
    if (qr > mid) {
        right = query(mid + 1, r, node * 2 + 1, ql, qr);
    }

    // 合并左右查询结果，规则与 pushup 相同：
    //   只有左 / 只有右：另一侧 sum、mul 为 0，交叉项自然为 0
    //   左右都有：mul = left.mul + right.mul + left.sum * right.sum
    return {(left.first + right.first) % MOD,
            (left.second + right.second + left.first * right.first % MOD) % MOD};
}

// 区间更新：将 [ql, qr] 内每个数加上 x
void update(int l, int r, int node, int ql, int qr, long long x) {
    // 当前节点被更新区间完全覆盖：打懒标记后直接返回（不再往下递归）
    if (ql <= l && qr >= r) {
        apply(node, l, r, x);
        return;
    }

    // 部分覆盖：先下推，再递归更新需要改动的儿子，最后用儿子信息回推
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) update(l, mid, node * 2, ql, qr, x);
    if (qr > mid) update(mid + 1, r, node * 2 + 1, ql, qr, x);
    pushup(node);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, q;
        cin >> n >> q;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        build(1, n, 1);

        while (q--) {
            int op;
            cin >> op;
            if (op == 1) {
                // 操作 1：区间 [l, r] 每个数加上 x
                int l, r;
                long long x;
                cin >> l >> r >> x;
                update(1, n, 1, l, r, x);
            } else if (op == 2) {
                // 操作 2：查询区间 [l, r] 的乘积和
                int l, r;
                cin >> l >> r;
                cout << query(1, n, 1, l, r).second << '\n';
            }
        }
    }
    return 0;
}
