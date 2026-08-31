#include <iostream>
#include <string>

using namespace std;

struct TrieNode {
  int isEndCnt;
  TrieNode *ch[26];
  TrieNode() : isEndCnt(0) { memset(ch, 0, sizeof(ch)); }
};

class Trie {

public:
  TrieNode *root;
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
    node->isEndCnt++;
  }
};

class Solution {

public:
  int numMatchingSubseq(string s, vector<string> &words) {
    Trie trie;
    for(string &word : words) {
        trie.insert(word);
    }

    // 对字典树进行遍历，然后检查是否是s的子序列
    TrieNode *node = trie.root;
    string currentWord = "";
    int count = 0;
    dfs(node, currentWord, s, count);
    return count;
  }

  void dfs(TrieNode *node, string &currentWord, string &s, int &count) {

    for (int i = 0;i < 26;i++) {
        if(node->ch[i] != nullptr) {
            currentWord += 'a' + i;
            if(node->ch[i]->isEndCnt > 0) {
                if(isSubSequence(s, currentWord)) {
                    count+=node->ch[i]->isEndCnt;
                    dfs(node->ch[i], currentWord, s, count);
                }
                // 如果当前序列不是子序列，则不需要进一步递归了, else块省略
            } else {
                dfs(node->ch[i], currentWord, s, count); 
            }
            currentWord.pop_back();
            
        }
    }
  }
  int isSubSequence(string &s, string &word) {
    int i = 0, j = 0;
    while (i < s.size() && j < word.size()) {
      if (s[i] == word[j]) {
        j++;
      }
      i++;
    }
    return j == word.size();
  }
};