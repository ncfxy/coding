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
	int myAtoi(string str) {
		bool plus = true,start = false;
		int ans = 0;
		for(int i = 0;i < str.length();i++){
			if(start){
				if(str[i] >= '0' && str[i] <= '9'){
					if(ans > 214748364 || (ans == 214748364 && str[i] >= '8')){
						if(plus)return 2147483647;
						else return -2147483648;
					}
					ans = ans * 10 + (str[i] - '0');
				}else{
					break;
				}
			}else{
				if(str[i] != ' '){
					start = true;
					if(str[i] == '-'){
						plus = false;
					}else{
						plus = true;
						if(str[i] == '+'){

						}else if(str[i] >= '0' && str[i] <= '9'){
							ans = ans * 10 + (str[i] - '0');
						}else{
							return 0;
						}
					}
				}
			}
		}
		if(!plus){
			return -ans;
		}
		return ans;

	}
};

int main() {
	string str = "      -122222222222222222";
	Solution so;
	cout << so.myAtoi(str);

	return 0;
}
