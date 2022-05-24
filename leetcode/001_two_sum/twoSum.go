// You can edit this code!
// Click here and start typing.
package main

import (
	"sort"
)

func twoSum(nums []int, target int) []int {
	result := make([]int, 2)
	myMap := make(map[int][]int)
	for idx, num := range nums {
		if _, ok := myMap[num]; ok {
			myMap[num] = append(myMap[num], idx)
		} else {
			myMap[num] = []int{idx}
		}
	}
	for key, idxList := range myMap {
		temp := target - key
		if _, ok := myMap[temp]; ok {
			result[0] = idxList[0]
			if temp == key && len(idxList) > 1 {
				result[1] = idxList[1]
				break
			} else if temp != key {
				result[1] = myMap[temp][0]
				break
			}
		}
	}
	sort.Ints(result)
	return result
}
