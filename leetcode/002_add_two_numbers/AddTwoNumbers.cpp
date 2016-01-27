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
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		int addExtra = 0;
		ListNode* ans = l1, *l1_father,*l2_father;
		while (l1 != NULL && l2 != NULL) {
			l1->val = l1->val + l2->val + addExtra;
			cout << l1->val <<endl;
			cout << addExtra << endl;
			addExtra = l1->val / 10;
			l1->val = l1->val % 10;
			l1_father = l1;
			l2_father = l2;
			l1 = l1->next;
			l2 = l2->next;
			delete l2_father;
		}
		if (l2 == NULL) {
			while (l1 != NULL) {
				l1->val = l1->val + addExtra;
				addExtra = l1->val / 10;
				l1->val = l1->val % 10;
				l1_father = l1;
				l1 = l1->next;
			}
		} else {
			l1_father->next = l2;
			l1 = l2;
			while (l1 != NULL) {
				l1->val = l1->val + addExtra;
				addExtra = l1->val / 10;
				l1->val = l1->val % 10;
				l1_father = l1;
				l1 = l1->next;
			}
		}
		if(addExtra > 0){
			ListNode* newNode = new ListNode(addExtra);
			l1_father->next = newNode;
		}
		return ans;
	}

}
;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	ListNode* l1 = new ListNode(8);
	l1->next = new ListNode(7);
	ListNode* l2 = new ListNode(2);
	l2->next = new ListNode(2);


	Solution so;
	ListNode* ans = so.addTwoNumbers(l1,l2);
	while(ans != NULL){
		cout << ans->val;
		ans = ans->next;
	}
	return 0;
}
