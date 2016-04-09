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
	bool isSelfCrossing(vector<int>& x) {
		if (x.size() < 4) {
			return false;
		}
		for (int i = 3; i < x.size(); i++) {
			if (i < 5) {
				if (x[i - 1] <= x[i - 3] && x[i] >= x[i - 2]) {
					return true;
				}
				if (i == 4 && x[4] + x[0] >= x[2] && x[1] == x[3]) {
					return true;
				}
			} else {
				if (x[i - 1] <= x[i - 3] && x[i] >= x[i - 2]) {
					return true;
				}
				if (x[i - 1] + x[i - 5] >= x[i - 3]
						&& x[i - 2] <= x[i - 4] + x[i] && x[i - 3] > x[i - 5]
						&& x[i - 3] > x[i - 5] && x[i - 2] > x[i - 4]
						&& x[i - 2] > x[i]) {
					return true;
				}
			}
		}
		return false;
	}

};

int main() {
	vector<int> ve;
	int nums[17] = { 1, 1, 2, 2, 3, 3, 4, 4, 10, 4, 4, 3, 3, 2, 2, 1, 1 };
	for (int i = 0; i < 17; i++) {
		ve.push_back(nums[i]);
	}
	Solution so;
	cout << so.isSelfCrossing(ve);

	return 0;
}
