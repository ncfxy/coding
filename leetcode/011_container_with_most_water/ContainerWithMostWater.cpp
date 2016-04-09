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
	int maxArea(vector<int>& height) {
		int i = 0, j = height.size() - 1;
		int water = 0;
		while(i < j){
			int h = min(height[i],height[j]);
			water = max(water,h * (j-i));
			while(height[i] <= h)i++;
			while(height[j] <= h)j--;
		}
		return water;
	}

};

int main() {
	vector<int> ve;
	ve.push_back(12);
	ve.push_back(20);
	ve.push_back(25);
	Solution so;
	cout << so.maxArea(ve);

	return 0;
}
