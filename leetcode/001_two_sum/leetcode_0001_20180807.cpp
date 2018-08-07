#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target){
        map<int, vector<int> > myMap;
        for (int i = 0; i < nums.size();i++){
            if(myMap.find(nums[i]) == myMap.end()){
                vector<int> ve;
                ve.push_back(i);
                myMap[nums[i]] = ve;
            } else {
                myMap[nums[i]].push_back(i);
            }
        }
        vector<int> ans;
        for (map<int, vector<int> >::iterator it = myMap.begin(); it != myMap.end();it++){
            int temp = target - it->first;
            map<int, vector<int> >::iterator it1 = myMap.find(temp);
            if(it1 != myMap.end()) {
                ans.push_back(it->second[0]);
                if(it != it1) {
                    ans.push_back(it1->second[0]);
                }else {
                    ans.push_back(it->second[1]);
                }
                break;
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};

int main() {
    cout << "Hello world!!" << endl;

    Solution so;
    vector<int> ve;
    ve.push_back(2);
    ve.push_back(7);
    ve.push_back(3);
    ve.push_back(15);
    vector<int> ans = so.twoSum(ve, 6);
    for (int i = 0; i < ans.size();i++){
        cout << ans[i] << " ";
    }
    cout << endl;
    cin >> ans[0];
    return 0;
}