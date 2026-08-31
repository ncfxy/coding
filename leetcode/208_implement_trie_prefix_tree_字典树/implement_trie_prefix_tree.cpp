#include <iostream>
#include <string>

using namespace std;

struct TrieNode {
  bool isEnd;
  TrieNode *ch[26];
  TrieNode() : isEnd(false) { memset(ch, 0, sizeof(ch)); }
};

class Trie {
  TrieNode *root;

  TrieNode *searchPrefix(string prefix) {
    TrieNode *node = root;
    for (char c : prefix) {
      int index = c - 'a';
      if (node->ch[index] == nullptr) {
        return nullptr;
      }
      node = node->ch[index];
    }
    return node;
  }

public:
  Trie() { root = new TrieNode(); }

  void insert(string word) {
    TrieNode *node = root;
    for (char c : word) {
      int index = c - 'a';
      if (node->ch[index] == nullptr) {
        node->ch[index] = new TrieNode();
      }
      node = node->ch[index];
    }
    node->isEnd = true;
  }

  bool search(string word) {
    TrieNode *node = searchPrefix(word);
    return node != nullptr && node->isEnd;
  }

  bool startsWith(string prefix) { return searchPrefix(prefix) != nullptr; }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */