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
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
	        int m = nums1.size(), n = nums2.size();
	        if (m > n) return findMedianSortedArrays(nums2, nums1);
	        int i, j, imin = 0, imax = m, half = (m + n + 1) / 2;
	        while (imin <= imax) {
	            i = (imin & imax) + ((imin ^ imax) >> 1);
	            j = half - i;
	            if (i > 0 && j < n && nums1[i - 1] > nums2[j]) imax = i - 1;
	            else if (j > 0 && i < m && nums2[j - 1] > nums1[i]) imin = i + 1;
	            else break;
	        }
	        int num1;
	        if (!i) num1 = nums2[j - 1];
	        else if (!j) num1 = nums1[i - 1];
	        else num1 = max(nums1[i - 1], nums2[j - 1]);
	        if ((m + n) & 1) return num1;
	        int num2;
	        if (i == m) num2 = nums2[j];
	        else if (j == n) num2 = nums1[i];
	        else num2 = min(nums1[i], nums2[j]);
	        return (num1 + num2) / 2.0;
	    }
};

int main() {
	vector<int> num1, num2;
	num1.push_back(2);
	num1.push_back(3);
	num1.push_back(4);


	num2.push_back(1);
	num2.push_back(5);
	num2.push_back(6);
	num2.push_back(7);
	Solution so;
	cout << so.findMedianSortedArrays(num1, num2);

	return 0;
}
