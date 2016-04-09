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

class Solution {
public:
	string longestCommonPrefix(vector<string>& strs) {
		if(strs.size() <= 0)return "";
		int longest = 0, i, j;
		for (i = 0; i < strs[0].length(); i++) {
			for (j = 0; j < strs.size(); j++) {
				if (strs[0][i] ^ strs[j][i]) {
					break;
				}
			}
			if (j == strs.size()) {
				longest++;
			}else{
				break;
			}
		}
		return strs[0].substr(0,longest);

	}

};

int main() {
	vector<string> str;
	str.push_back("sss");
	Solution so;
	cout << so.longestCommonPrefix(str);

	return 0;
}
