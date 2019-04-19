/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 */
var twoSum = function (nums, target) {
    var ans = [];
    var myMap = {};
    nums.forEach(function(num, index){
        myMap[num] ? myMap[num].push(index) : myMap[num] = [index];
    });
    var isBreak = false;
    Object.keys(myMap).forEach(function(key){
        if(isBreak)return;
        var temp = target - key;
        if(myMap[temp]){
            ans.push(myMap[key][0]);
            ans.push(temp == key ? myMap[key][1] : myMap[temp][0]);
            isBreak = true;
        }
    });
    ans.sort();
    return ans;
};

var nums = [2, 7, 11, 15];
var target = 9;
// var nums = [3,3];
// var target = 6;
console.log(twoSum(nums, target));