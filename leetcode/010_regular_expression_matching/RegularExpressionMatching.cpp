/*
 * AddTwoNumbers.cpp
 *
 *  Created on: 2016Äê1ÔÂ27ÈÕ
 *      Author: ncfxy
 */

#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <string>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

class Solution {
public:
	bool isMatch(string s, string p) {
		return dfs(s,p,0,0);
	}

	bool dfs(string s, string p, int a, int b) {
		if (a == s.length() && b == p.length()) {
			return true;
		}
		if (a == s.length()) {
			if(p[b+1] == '*'){
				return dfs(s,p,a,b+2);
			}else{
				return false;
			}
		} else if (b == p.length()) {
			return false;
		} else {
			if(p[b+1] == '*'){
				if(s[a] == p[b] || (s[a] != p[b] && p[b] == '.')){
					return dfs(s,p,a+1,b) || dfs(s,p,a,b+2);
				}else{
					return dfs(s,p,a,b+2);
				}
			}else{
				if(s[a] == p[b] || (s[a] != p[b] && p[b] == '.')){
					return dfs(s,p,a+1,b+1);
				}else{
					return false;
				}
			}
		}
	}

};

int main() {
	int a = 12321;
	string str1 = "aaa";
	string str2 = "a*a";
	Solution so;
	cout << so.isMatch(str1, str2);

	return 0;
}
