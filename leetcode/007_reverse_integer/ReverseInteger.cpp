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
	int reverse(int x){
		if(x == -2147483648){
			return 0;
		}
		if(x < 0){
			return - reverse(-x);
		}
		long long ans = 0;
		while(x){
			int tmp = x % 10;
			if(ans > 214748364 || (ans == 214748364 && tmp > 7)){
				return 0;
			}
			ans = ans * 10 + tmp;
			x = x / 10;
		}
		return ans;
	}
};

int main() {
	int x = -2147483641;
	cout << x<<endl;
	cout << -x<<endl;
	Solution so;
	cout << so.reverse(x);

	return 0;
}
