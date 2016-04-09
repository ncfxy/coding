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
	string convert(string s, int numRows) {
		if(numRows == 1){
			return s;
		}
		string s1[numRows + 1];
		int index = 0;
		bool down = true;
		for(int i = 0;i < s.length();i++){
			if(index == 0){
				s1[index] += s[i];
				down = true;
				index++;
			}else if(index == numRows-1){
				s1[index] += s[i];
				down = false;
				index--;
			}else{
				s1[index] += s[i];
				if(down){
					index++;
				}else{
					index--;
				}
			}
		}
		string ans = "";
		for(int i = 0;i < numRows;i++){
			ans += s1[i];
		}
		return ans;
	}
};

int main() {
	string s = "PAYPALISHIRING";
	Solution so;
	cout << so.convert(s, 3);

	return 0;
}
