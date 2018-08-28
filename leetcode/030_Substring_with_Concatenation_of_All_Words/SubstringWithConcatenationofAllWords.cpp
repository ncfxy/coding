#include <cstdio>
#include <cstdlib>
#include <hash_map>
#include <iostream>
#include <map>

using namespace std;

class Solution
{
  public:
    vector<int> findSubstring(string s, vector<string> &words)
    {
        vector<int> result;
        if (s.length() == 0 || words.empty())
        {
            return result;
        }
        map<string, int> wordMap;
        for (int i = 0; i < words.size(); i++)
        {
            if(wordMap.find(words[i]) != wordMap.end()){
                wordMap[words[i]] = wordMap[words[i]] + 1;
            }else {
                wordMap[words[i]] = 1;
            }
        }

        int sLength = s.length();
        int wordLength = words[0].length();
        vector<string> splitBuffer;
        for (int start = 0; start < wordLength; start++)
        {
            splitBuffer.clear();
            int index = start;
            while (index + wordLength <= sLength)
            {
                string splitWord = s.substr(index, wordLength);
                splitBuffer.push_back(splitWord);
                index += wordLength;
            }
            int left = 0, right = 0;
            bool atLeastOne = false;
            while (right < splitBuffer.size()+1)
            {
                if (right - left == words.size() && atLeastOne)
                {
                    result.push_back(start + left * wordLength);
                    wordMap[splitBuffer[left]]++;
                    left++;
                }
                if(right == splitBuffer.size()){
                    while (left < right)
                    {
                        wordMap[splitBuffer[left]]++;
                        left++;
                    }
                    break;
                }
                map<string, int>::iterator it = wordMap.find(splitBuffer[right]);
                if (it != wordMap.end())
                {
                    if (it->second > 0)
                    {
                        it->second--;
                        atLeastOne = true;
                    }
                    else
                    {
                        while (splitBuffer[left] != splitBuffer[right])
                        {
                            wordMap[splitBuffer[left]]++;
                            left++;
                        }
                        left++;
                    }
                }
                else
                {
                    atLeastOne = false;
                    while (left < right)
                    {
                        wordMap[splitBuffer[left]]++;
                        left++;
                    }
                    left++;
                }
                right++;
            }
        }
        return result;
    }
};

int main()
{
    Solution so;
    string s = "";
    vector<string> words;
    vector<int> result;
    // string s = "barfoothefoobarman";
    // words.clear();
    // words.push_back("foo");
    // words.push_back("bar");
    // result = so.findSubstring(s, words);
    // for (int i = 0; i < result.size(); i++)
    // {
    //     cout << result[i] << endl;
    // }
    // s = "wordgoodgoodgoodbestword";
    // words.clear();
    // words.push_back("word");
    // words.push_back("good");
    // words.push_back("best");
    // words.push_back("good");
    // result = so.findSubstring(s, words);
    // for (int i = 0; i < result.size(); i++)
    // {
    //     cout << result[i] << endl;
    // }

    s = "aaaaaaaa";
    words.clear();
    words.push_back("aa");
    words.push_back("aa");
    words.push_back("aa");
    result = so.findSubstring(s, words);
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << endl;
    }
    system("pause");
    return 0;
}