/*
 * AddTwoNumbers.cpp
 *
 *  Created on: 2016��1��27��
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
public:
	int lengthOfLongestSubstring(string s) {
		vector<int> ve[256];
		int str_length = s.length();
		int index[str_length+1];
		for (int i = 0; i < 256; i++) {
			ve[i].clear();
		}
		for (int i = 0; i < str_length; i++) {
			int temp = (int) (s[i]);
			ve[temp].push_back(i);
		}
		for(int i = 0;i < 256;i++){
			for(int j = 0;j < ve[i].size();j++){
				if(j == ve[i].size()-1){
					index[ve[i][j]] = str_length;
				}else{
					index[ve[i][j]] = ve[i][j+1];
				}
			}
		}
		int ans = 0;
		int end = str_length;
		for(int i = str_length-1;i >=0 ;i--){
			if(index[i] < end){
				end = index[i];
			}
			if(end - i > ans){
				ans = end -i;
			}
		}
		return ans;
	}

}
;

int main() {
	string str = "abcabcbb";
	Solution so;
	cout << so.lengthOfLongestSubstring(str);

	return 0;
}
