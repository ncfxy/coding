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
	bool isPalindrome(int x) {
		if (x < 0 || (x != 0 && x % 10 == 0))
			return false;
		int sum = 0;
		while (x > sum) {
			sum = sum * 10 + x % 10;
			x = x / 10;
		}
		return (x == sum) || (x == sum / 10);
	}
};

int main() {
	int a = 12321;
	string str;
	Solution so;
	cout << so.isPalindrome(a);

	return 0;
}
