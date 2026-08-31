#include <iostream>
#include <string>

using namespace std;

struct TrieNode {
    TrieNode *ch[26];
    int val;
    TrieNode() : val(0) { memset(ch, 0, sizeof(ch)); }
};

class MapSum {
    TrieNode *root;
    unordered_map<string, int> cnt;
public:
  MapSum() {
    root = new TrieNode();
  }

  void insert(string key, int val) {
    int delta = val;
    if(cnt.count(key)) delta -= cnt[key];
    cnt[key] = val;
    TrieNode *node = root;
    for (char c : key) {
        int index = c - 'a';
        if (node->ch[index] == nullptr) {
            node->ch[index] = new TrieNode();
        }
        node = node->ch[index];
        node->val +=delta;
    }
  }

  int sum(string prefix) {
    TrieNode *node = root;
    for (char c : prefix) {
        int index = c - 'a';
        if (node->ch[index] == nullptr) {
            return 0;
        }
        node = node->ch[index];
    }
    return node->val;
  }
};