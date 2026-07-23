#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    public:

        // 声明线段树数组
        vector<int> segmentTree;

        int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
            
            segmentTree.resize(baskets.size() * 4);
            buildSegmentTree(baskets, 0, baskets.size() - 1, 1);
            int result = 0;
            for (int i = 0; i < fruits.size(); i++) {
                int index = querySegmentTree(0, baskets.size() - 1, 1, fruits[i]);
                if (index != -1) {
                    updateSegmentTree(index);
                } else {
                    result++;
                }
            }
            return result;
        }

        // 通过baskets，递归构建线段树，记录最大值
        void buildSegmentTree(vector<int>& baskets, int left, int right, int index) {
            if (left == right) {
                segmentTree[index] = baskets[left];
                return;
            }
            int mid = (left + right) / 2;
            buildSegmentTree(baskets, left, mid, index * 2);
            buildSegmentTree(baskets, mid + 1, right, index * 2 + 1);
            segmentTree[index] = max(segmentTree[index * 2], segmentTree[index * 2 + 1]);
        }

        // 查询线段树,查询第一个大于等于 val 的值，如果未查询到，返回-1
        int querySegmentTree(int left, int right, int index, int val) {
            if (left == right) {
                return segmentTree[index] >= val ? index : -1;
            }
            if (segmentTree[index] < val) {
                return -1;
            }
            int mid = (left + right) / 2;

            if (segmentTree[index * 2] >= val) {
                return querySegmentTree(left, mid, index * 2, val);
            }
            return querySegmentTree(mid + 1, right, index * 2 + 1, val);
        }

        // 更新线段树，把查询到的index对应的值，修改成-1，并更新线段树
        void updateSegmentTree(int index) {
            segmentTree[index] = -1;
            while (index > 0) {
                index /= 2;
                segmentTree[index] = max(segmentTree[index * 2], segmentTree[index * 2 + 1]);
            }
        }
};

int main() {
    Solution solution;
    vector<int> fruits = {1, 2, 3, 4, 5};
    vector<int> baskets = {2, 3};
    cout << solution.numOfUnplacedFruits(fruits, baskets) << endl;

    // 输入： fruits = [4,2,5], baskets = [3,5,4]
    // 输出： 1
    fruits = {4, 2, 5};
    baskets = {3, 5, 4};
    cout << solution.numOfUnplacedFruits(fruits, baskets) << endl;
    // 输入： fruits = [3,6,1], baskets = [6,4,7]
    // 输出： 0
    fruits = {3, 6, 1};
    baskets = {6, 4, 7};
    cout << solution.numOfUnplacedFruits(fruits, baskets) << endl;
    return 0;
}