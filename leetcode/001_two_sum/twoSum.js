/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 */
var twoSum = function (nums, target) {
    var ans = [];
    var myMap = {};
    for (var i = 0; i < nums.length;i++){
        if (Object.keys(myMap).indexOf(nums[i].toString()) != -1) {
            myMap[nums[i]].push(i);
        } else {
            myMap[nums[i]] = [i];
        }
    }

    var keys = Object.keys(myMap);
    for (var i = 0; i < keys.length; i++){
        var key = keys[i];
        temp = target - key;
        if (keys.indexOf(temp.toString()) != -1) {
            ans.push(myMap[key][0]);
            if (temp == key) {
                ans.push(myMap[key][1]);
            } else {
                ans.push(myMap[temp][0]);
            }
            break;
        }
    }
    ans.sort();
    return ans;
};

var nums = [2, 7, 11, 15];
var target = 9;
// var nums = [3,3];
// var target = 6;
console.log(twoSum(nums, target));