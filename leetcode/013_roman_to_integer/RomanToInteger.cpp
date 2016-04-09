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
	int romanToInt(string s) {
		int ans = toNumber(s[0]);
		for(int i = 1;i < s.length();i++){
			if(toNumber(s[i-1]) < toNumber(s[i])){
				ans += toNumber(s[i]) - 2 * toNumber(s[i-1]);
			}else{
				ans += toNumber(s[i]);
			}
		}
		return ans;

	}

	int toNumber(char ch) {
		switch (ch) {
		case 'I':
			return 1;
		case 'V':
			return 5;
		case 'X':
			return 10;
		case 'L':
			return 50;
		case 'C':
			return 100;
		case 'D':
			return 500;
		case 'M':
			return 1000;
		}
		return 0;
	}

};

int main() {
	string num = "MCMXCVI";
	Solution so;
	cout << so.romanToInt(num);

	return 0;
}
