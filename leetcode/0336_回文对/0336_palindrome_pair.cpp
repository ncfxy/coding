#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Trie 节点
    struct Node {
        int headEdge;   // 第一条儿子边
        int terminal;   // 是否有字符串在这里结束
        int palHead;    // palindrome list 链表头

        Node() : headEdge(-1), terminal(-1), palHead(-1) {}
    };

    // Trie 的边
    struct Edge {
        int to;
        int next;
        unsigned char ch;

        Edge(int _to, int _next, int _ch)
            : to(_to), next(_next), ch(_ch) {}
    };

    // 节点上的 palindrome list
    struct PalItem {
        int wordId;
        int next;

        PalItem(int _wordId, int _next)
            : wordId(_wordId), next(_next) {}
    };

    vector<Node> trie;
    vector<Edge> edges;
    vector<PalItem> palItems;

    /*
     * Manacher
     *
     * prefix[len]：
     *     s[0 .. len-1] 是否是回文
     *
     * suffix[pos]：
     *     s[pos .. n-1] 是否是回文
     */
    void getPalindromeInfo(
        const string& s,
        vector<char>& prefix,
        vector<char>& suffix
    ) {
        int n = s.size();

        prefix.assign(n + 1, false);
        suffix.assign(n + 1, false);

        // 空串是回文
        prefix[0] = true;
        suffix[n] = true;

        if (n == 0)
            return;

        // d1[i]：以 i 为中心的最长奇数回文半径
        vector<int> d1(n);

        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k;

            if (i > r)
                k = 1;
            else
                k = min(d1[l + r - i], r - i + 1);

            while (
                i - k >= 0 &&
                i + k < n &&
                s[i - k] == s[i + k]
            ) {
                ++k;
            }

            d1[i] = k;

            if (i + k - 1 > r) {
                l = i - k + 1;
                r = i + k - 1;
            }
        }

        // d2[i]：中心在 i-1 和 i 之间的最长偶数回文半径
        vector<int> d2(n);

        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k;

            if (i > r)
                k = 0;
            else
                k = min(d2[l + r - i + 1], r - i + 1);

            while (
                i - k - 1 >= 0 &&
                i + k < n &&
                s[i - k - 1] == s[i + k]
            ) {
                ++k;
            }

            d2[i] = k;

            if (i + k - 1 > r) {
                l = i - k;
                r = i + k - 1;
            }
        }

        /*
         * 根据 Manacher 的结果，只关心：
         *
         * 1. 是否碰到左边界 -> 回文前缀
         * 2. 是否碰到右边界 -> 回文后缀
         */

        // 奇数回文
        for (int i = 0; i < n; ++i) {
            int left = i - d1[i] + 1;
            int right = i + d1[i] - 1;

            if (left == 0) {
                prefix[right + 1] = true;
            }

            if (right == n - 1) {
                suffix[left] = true;
            }
        }

        // 偶数回文
        for (int i = 0; i < n; ++i) {
            if (d2[i] == 0)
                continue;

            int left = i - d2[i];
            int right = i + d2[i] - 1;

            if (left == 0) {
                prefix[right + 1] = true;
            }

            if (right == n - 1) {
                suffix[left] = true;
            }
        }
    }

    // 找儿子节点
    int findChild(int node, int ch) {
        for (int e = trie[node].headEdge; e != -1; e = edges[e].next) {
            if (edges[e].ch == ch)
                return edges[e].to;
        }

        return -1;
    }

    // 找不到则创建
    int getOrCreateChild(int node, int ch) {
        int child = findChild(node, ch);

        if (child != -1)
            return child;

        child = trie.size();
        trie.emplace_back();

        edges.emplace_back(
            child,
            trie[node].headEdge,
            ch
        );

        trie[node].headEdge = edges.size() - 1;

        return child;
    }

    // 向节点的 palindrome list 添加字符串编号
    void addPalindromeWord(int node, int id) {
        palItems.emplace_back(
            id,
            trie[node].palHead
        );

        trie[node].palHead = palItems.size() - 1;
    }

    /*
     * 倒序插入字符串
     */
    void insertWord(
        const string& s,
        int id,
        const vector<char>& prefix
    ) {
        int node = 0;
        int n = s.size();

        /*
         * 倒着插入。
         *
         * 目前已经插入 s[k+1 .. n-1] 的逆序。
         *
         * 如果剩余的：
         *
         * s[0 .. k]
         *
         * 是回文，则把 id 放入当前节点 palList。
         */
        for (int k = n - 1; k >= 0; --k) {

            if (prefix[k + 1]) {
                addPalindromeWord(node, id);
            }

            int ch = s[k] - 'a';
            node = getOrCreateChild(node, ch);
        }

        trie[node].terminal = id;

        // 剩余前缀为空串，也是回文
        addPalindromeWord(node, id);
    }

public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        trie.clear();
        edges.clear();
        palItems.clear();

        trie.emplace_back();    // root

        int totalLength = 0;

        for (const string& s : words)
            totalLength += s.size();

        trie.reserve(totalLength + 1);
        edges.reserve(totalLength);
        palItems.reserve(totalLength + words.size());

        vector<char> prefix, suffix;

        /*
         * 第一遍：
         * 将所有字符串倒序插入 Trie。
         */
        for (int i = 0; i < (int)words.size(); ++i) {

            getPalindromeInfo(
                words[i],
                prefix,
                suffix
            );

            insertWord(
                words[i],
                i,
                prefix
            );
        }

        vector<vector<int>> ans;

        /*
         * 第二遍：
         * 正序查询每个字符串。
         */
        for (int i = 0; i < (int)words.size(); ++i) {

            const string& s = words[i];
            int n = s.size();

            getPalindromeInfo(
                s,
                prefix,
                suffix
            );

            int node = 0;
            bool matched = true;

            for (int p = 0; p < n; ++p) {

                /*
                 * 当前节点正好是另一个字符串 j 的终点。
                 *
                 * Trie 中匹配的部分说明：
                 *
                 * words[j] =
                 * reverse(s[0 .. p-1])
                 *
                 * 如果剩余：
                 *
                 * s[p .. n-1]
                 *
                 * 是回文，则：
                 *
                 * s + words[j]
                 *
                 * 是回文。
                 */
                int j = trie[node].terminal;

                if (
                    j != -1 &&
                    j != i &&
                    suffix[p]
                ) {
                    ans.push_back({i, j});
                }

                int ch = s[p] - 'a';

                node = findChild(node, ch);

                if (node == -1) {
                    matched = false;
                    break;
                }
            }

            if (!matched)
                continue;

            /*
             * s 已经完全匹配。
             *
             * 当前节点 palList 中的字符串 j 满足：
             *
             * words[j] =
             * 回文前缀 + reverse(s)
             *
             * 所以：
             *
             * s + words[j]
             *
             * 一定是回文。
             */
            for (
                int item = trie[node].palHead;
                item != -1;
                item = palItems[item].next
            ) {
                int j = palItems[item].wordId;

                if (j != i) {
                    ans.push_back({i, j});
                }
            }
        }

        return ans;
    }
};