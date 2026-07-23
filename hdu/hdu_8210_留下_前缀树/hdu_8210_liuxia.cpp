#include <cstdint>
#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

// ========== 常量 ==========
// B：按 30 位二进制处理 x（题目里 a,b,x 都在 30 位范围内）
static constexpr int B = 30;
// UNK：符号尚未确定（对应题解里的 "?"）
// 确定后：+1 表示 f>0，-1 表示 f<0
static constexpr int UNK = 2;
// 哈希表每个槽位用一个 uint64 打包：高 44 位存 key，低 20 位存最小下标
static constexpr int SHIFT = 20;
static constexpr uint64_t LOW_MASK = (1ULL << SHIFT) - 1;
static constexpr int INF = 1e9;

// ========== 稀疏哈希表：存「前缀块 -> 最左合法下标」 ==========
//
// 前缀块的编码方式：
//   key = (1 << depth) | prefix
// 其中：
//   depth  = 前缀长度（已确定的二进制位数，0~30）
//   prefix = 这 depth 位本身的数值
// 例如 depth=2, prefix=2(二进制 10) → key = (1<<2)|2 = 4|2 = 6
//
// 为什么前面加 (1<<depth)？
//   不同长度的前缀可能数值相同（比如 "1" 和 "01"），需要区分 depth。
//   加上最高位 1 后，不同 depth 的 key 落在不同区间，不会撞车。
//
struct MinHash {
    vector<uint64_t> table; // 开放寻址哈希表；0 表示空槽
    size_t mask;            // 容量-1，用 & mask 代替 % capacity

    // 把 key 打散，降低哈希冲突
    static uint64_t mix(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }

    explicit MinHash(int n) {
        // 估计最多会插入多少个不同 key，用来定哈希表容量。
        // 直觉：每一层 depth 上，合法前缀块数量不会超过 min(2^d, 约 2n)。
        uint64_t upper = 0;
        for (int d = 0; d <= B; ++d) {
            upper += min(1ULL << d, 2ULL * n);
        }

        // 容量取 2 的幂，且装载率控制在约 0.7 以下
        uint64_t cap = 1;
        while (cap * 7 < upper * 10) cap <<= 1;

        table.assign(cap, 0);
        mask = cap - 1;
    }

    // 写入 / 更新：把 key 对应的最小值压到 value（取更小的下标）
    void relax(uint32_t key, int value) {
        size_t p = mix(key) & mask;

        while (true) {
            uint64_t cur = table[p];

            if (cur == 0) {
                // 空槽：直接写入  (key << 20) | value
                table[p] = (uint64_t(key) << SHIFT) | value;
                return;
            }

            if (uint32_t(cur >> SHIFT) == key) {
                // 已有同一 key：只保留更小的下标
                if (int(cur & LOW_MASK) > value) {
                    table[p] = (uint64_t(key) << SHIFT) | value;
                }
                return;
            }

            // 开放寻址：线性探测下一个槽
            p = (p + 1) & mask;
        }
    }

    // 查询 key 对应的最小下标；不存在则返回 INF
    int get(uint32_t key) const {
        size_t p = mix(key) & mask;

        while (true) {
            uint64_t cur = table[p];
            if (cur == 0) return INF; // 碰到空槽，说明从未插入过这个 key

            if (uint32_t(cur >> SHIFT) == key) {
                return int(cur & LOW_MASK);
            }

            p = (p + 1) & mask;
        }
    }
};

// ========== 对一对相邻位置 (i, i+1) 做 DFS，枚举合法前缀块 ==========
//
// 状态含义（s1 / s2）：
//   UNK(=2) : 到目前为止 x 仍与对应的 c 相同，f 的符号还没定
//   +1      : 已经确定 f > 0
//   -1      : 已经确定 f < 0
//
// 规则回顾：
//   x 与 c 第一次不同的那一位上：
//     若 b 该位是 0 → f > 0
//     若 b 该位是 1 → f < 0
//   若 x 最终等于某个 c → 对应 f = 0，乘积一定 <= 0
struct Emitter {
    MinHash &mp;
    uint32_t c1, b1; // 左位置：c = a xor b，以及原 b
    uint32_t c2, b2; // 右位置
    int idx;         // 这对相邻位置的答案下标（题目从 1 开始）

    explicit Emitter(MinHash &mp) : mp(mp) {}

    // 把当前前缀块记为「对这个 idx 合法」
    void addBlock(int depth, uint32_t prefix) {
        uint32_t key = (uint32_t(1) << depth) | prefix;
        mp.relax(key, idx); // 同一 key 只保留最左的 idx
    }

    // depth : 已经确定的位数（也是递归深度）
    // s1/s2 : 左右位置当前的符号状态
    // prefix: 已经填好的高 depth 位
    void dfs(int depth, int s1, int s2, uint32_t prefix) {
        // 两个符号都定了：
        //   不同 → 一正一负，整块合法
        //   相同 → 同号，整块不合法，直接丢弃
        if (s1 != UNK && s2 != UNK) {
            if (s1 != s2) addBlock(depth, prefix);
            return;
        }

        // 已经填完 30 位，但仍有 UNK：
        // 说明 x 恰好等于某个还在 UNK 的 c，对应 f=0，合法
        if (depth == B) {
            addBlock(depth, prefix);
            return;
        }

        // 当前要填的是从高位往下数第 depth 位，对应 bit 号 = B-1-depth
        // 例如 depth=0 时填第 29 位（最高位）
        int bit = B - 1 - depth;
        int cbit1 = (c1 >> bit) & 1; // c1 在这一位上的值
        int cbit2 = (c2 >> bit) & 1;

        // 枚举 x 的下一位填 0 或 1
        for (int go = 0; go <= 1; ++go) {
            int ns1 = s1, ns2 = s2;

            // 若左位置还是 UNK，且这一位第一次与 c1 不同 → 立刻定符号
            if (ns1 == UNK && go != cbit1) {
                // b 该位为 1 → f<0(-1)；为 0 → f>0(+1)
                ns1 = ((b1 >> bit) & 1) ? -1 : 1;
            }
            // 右位置同理
            if (ns2 == UNK && go != cbit2) {
                ns2 = ((b2 >> bit) & 1) ? -1 : 1;
            }
            // 若 go 与 c 相同，状态保持 UNK，继续往下走

            // prefix 左移一位，低位接上 go，得到更长的前缀
            dfs(depth + 1, ns1, ns2, (prefix << 1) | go);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, q;
        cin >> n >> q;

        // c[i] 最终存的是 a_i xor b_i
        // 输入时先把 a 读进 c，再读 b 并异或进去
        vector<uint32_t> c(n), b(n);

        for (int i = 0; i < n; ++i) cin >> c[i]; // 暂存 a_i
        for (int i = 0; i < n; ++i) {
            cin >> b[i];
            c[i] ^= b[i]; // c_i = a_i xor b_i
        }

        MinHash mp(n);
        Emitter emitter(mp);

        // ---- 预处理：对每一对相邻位置，DFS 出所有合法前缀块 ----
        for (int i = 0; i + 1 < n; ++i) {
            emitter.c1 = c[i];
            emitter.b1 = b[i];
            emitter.c2 = c[i + 1];
            emitter.b2 = b[i + 1];
            emitter.idx = i + 1; // 题目下标从 1 开始，答案输出 i+1

            // 从空前缀开始，两边符号都还是 UNK
            emitter.dfs(0, UNK, UNK, 0);
        }

        // ---- 回答询问 ----
        while (q--) {
            uint32_t x;
            cin >> x;

            int ans = INF;

            // 查询思路：
            //   预处理时存的是「某些前缀块合法，对应某个最左下标」。
            //   现在给了具体的 x，只要查「所有覆盖这个 x 的前缀块」。
            //
            // 一个数 x 恰好被自己这条前缀链覆盖，例如假设 B=3、x=5=101：
            //   depth=0:  ***（空前缀，覆盖所有数）  prefix=0
            //   depth=1:  1**（最高 1 位是 1）      prefix=1   ← x>>2
            //   depth=2:  10*（最高 2 位是 10）     prefix=2   ← x>>1
            //   depth=3:  101（完整的 x）           prefix=5   ← x>>0
            // 所以循环 depth=0..B，逐个取出这些前缀去查表即可。
            for (int depth = 0; depth <= B; ++depth) {
                // 第 1 步：取出 x 的最高 depth 位，得到 prefix 的数值
                //   depth=0 时没有位，约定 prefix=0
                //   否则把 x 右移 (B-depth) 位，丢掉低位，只留下高 depth 位
                //   例：B=3, x=101, depth=2 → x>>(3-2)=x>>1 → 10(二进制)=2
                uint32_t prefix = (depth == 0 ? 0 : (x >> (B - depth)));

                // 第 2 步：编成和预处理时相同的 key
                //   key = (1 << depth) | prefix
                //   前面那个 1 用来区分「不同长度」的前缀，避免撞车
                //   例：depth=2, prefix=2 → key = 100|010 = 110(二进制)=6
                uint32_t key = (uint32_t(1) << depth) | prefix;

                // 第 3 步：查这个前缀块对应的最左下标，全局取最小
                //   没存过这个 key 时 get 返回 INF，不影响 min
                ans = min(ans, mp.get(key));
            }

            cout << (ans == INF ? -1 : ans) << '\n';
        }
    }

    return 0;
}
