#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct TrieNode {
  bool isEnd;
  TrieNode *ch[26];
  TrieNode() : isEnd(false) { memset(ch, 0, sizeof(ch)); }
};

class Trie {
    TrieNode *root;
  
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

    string search(string &s) { // 查找s在字典树中存在的最短前缀
        TrieNode *node = root;
        string ans = "";
        for (char c : s) {
            int index = c - 'a';
            if(node->isEnd) {
                return ans;
            }
            if(node->ch[index] == nullptr) {
                return "";
            }
            ans += c;
            node = node->ch[index];
        }
        return ans;
    }
  
  };


class Solution {
public:
  string replaceWords(vector<string> &dictionary, string sentence) {

    Trie trie;
    for (string &word : dictionary) {
        trie.insert(word);
    }
    string ans = "";
    stringstream ss(sentence);
    string word;
    while (ss >> word) {
        string str = trie.search(word);
        if(str == "") ans += word + ' ';
        else ans += str + ' ';
    }
    ans.pop_back();
    return ans;
  }
};