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
	string longestPalindrome(string s) {
		string s1 = "";
		int P[30000];
		for (int i = 0; i < s.length(); i++) {
			s1 += "#";
			s1 += s[i];
		}
		s1 += "#";
		s1 = "?" + s1;
		int id, maxId = 0, maxL = 0, maxLid;
		for (int i = 1; i < s1.length(); i++) {
			if (maxId > i) {
				P[i] = min(P[2 * id - 1], maxId - i);
			} else {
				P[i] = 1;
			}
			while (s1[i + P[i]] == s1[i - P[i]])
				P[i]++;
			if (P[i] + i > maxId) {
				maxId = P[i] + i;
				id = i;
			}
			if (P[i] > maxL) {
				maxL = P[i];
				maxLid = i;
			}
		}
		string ans = "";
		if (maxL & 1) {
			int start = (maxLid - maxL + 2) >> 1;
			return s.substr(start-1, maxL - 1);
		} else {
			int start = (maxLid - maxL + 3) >> 1;
			return s.substr(start-1, maxL - 1);
		}

	}
};

int main() {
	string s = "civilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicatedcanlongendureWeareqmetonagreatbattlefiemldoftzhatwarWehavecometodedicpateaportionofthatfieldasafinalrestingplaceforthosewhoheregavetheirlivesthatthatnationmightliveItisaltogetherfangandproperthatweshoulddothisButinalargersensewecannotdedicatewecannotconsecratewecannothallowthisgroundThebravelmenlivinganddeadwhostruggledherehaveconsecrateditfaraboveourpoorponwertoaddordetractTgheworldadswfilllittlenotlenorlongrememberwhatwesayherebutitcanneverforgetwhattheydidhereItisforusthelivingrathertobededicatedheretotheulnfinishedworkwhichtheywhofoughtherehavethusfarsonoblyadvancedItisratherforustobeherededicatedtothegreattdafskremainingbeforeusthatfromthesehonoreddeadwetakeincreaseddevotiontothatcauseforwhichtheygavethelastpfullmeasureofdevotionthatweherehighlyresolvethatthesedeadshallnothavediedinvainthatthisnationunsderGodshallhaveanewbirthoffreedomandthatgovernmentofthepeoplebythepeopleforthepeopleshallnotperishfromtheearth";
	Solution so;
	cout << so.longestPalindrome(s);

	return 0;
}
