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
	string intToRoman(int num) {
		string M[] = { "", "M", "MM", "MMM" };
		string C[] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC",
				"CM" };
		string X[] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX",
				"XC" };
		string I[] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII",
				"IX" };
		return M[num / 1000] + C[(num % 1000) / 100] + X[(num % 100) / 10]
				+ I[num % 10];
	}

};

int main() {
	int num = 123;
	Solution so;
	cout << so.intToRoman(num);

	return 0;
}
