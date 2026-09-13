#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
        string shortestPalindrome(string s) {
            if (s.empty()) return "";
            int n = s.size();
            string rev = s;
            reverse(rev.begin(), rev.end());
    
            // 滚动哈希参数
            const unsigned long long BASE = 131;
            const unsigned long long MOD = 1e9 + 7; // 单哈希，实际可用双哈希降低碰撞
    
            // 预处理幂次
            vector<unsigned long long> pow(n + 1, 1);
            for (int i = 1; i <= n; ++i) {
                pow[i] = (pow[i-1] * BASE) % MOD;
            }
    
            // 计算 s 的前缀哈希
            vector<unsigned long long> hs(n + 1, 0);
            for (int i = 0; i < n; ++i) {
                hs[i+1] = (hs[i] * BASE + s[i]) % MOD;
            }
    
            // 计算 rev 的前缀哈希
            vector<unsigned long long> hr(n + 1, 0);
            for (int i = 0; i < n; ++i) {
                hr[i+1] = (hr[i] * BASE + rev[i]) % MOD;
            }
    
            // 获取子串哈希的 lambda
            auto getHash = [&](const vector<unsigned long long>& h, int l, int r) -> unsigned long long {
                // 子串 h[l..r] 的哈希
                unsigned long long res = (h[r+1] - h[l] * pow[r-l+1] % MOD + MOD) % MOD;
                return res;
            };
    
            // 从大到小找最长回文前缀
            int l = 0;
            for (int len = n; len >= 1; --len) {
                // s[0..len-1] 的哈希
                unsigned long long hash_s = getHash(hs, 0, len - 1);
                // rev[n-len .. n-1] 的哈希
                unsigned long long hash_rev = getHash(hr, n - len, n - 1);
                if (hash_s == hash_rev) {
                    l = len;
                    break;
                }
            }
    
            // 构造答案
            return rev.substr(0, n - l) + s;
        }
    };