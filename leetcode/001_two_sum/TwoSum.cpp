/*
 * two_sum.cpp
 *
 *  Created on: 2016Äê1ÔÂ27ÈÕ
 *      Author: ncfxy
 */

#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		map<int, vector<int> > myMap;
		for (int i = 0; i < nums.size(); i++) {
			if (myMap.find(nums[i]) == myMap.end()) {
				vector<int> ve;
				ve.push_back(i + 1);
				myMap[nums[i]] = ve;
			} else {
				myMap[nums[i]].push_back(i + 1);
			}
		}
		vector<int> ans;
		for (map<int, vector<int> >::iterator it = myMap.begin();
				it != myMap.end(); it++) {
			int temp = target - it->first;
			map<int, vector<int> >::iterator it1 = myMap.find(temp);
			if (it1 != myMap.end()) {
				ans.insert(ans.end(), it->second.begin(), it->second.end());
				if (it != it1) {
					ans.insert(ans.end(), it1->second.begin(),
							it1->second.end());
				}
				break;
			}
		}
		sort(ans.begin(), ans.end());
		return ans;
	}

}
;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	Solution so;
	vector<int> ve;
	ve.push_back(3);
	ve.push_back(5);
	ve.push_back(7);
	ve.push_back(10);
	so.twoSum(ve, 12);
	return 0;
}

