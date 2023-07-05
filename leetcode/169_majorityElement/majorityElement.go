package main

// 摩尔投票法

func majorityElement(nums []int) int {
	current := nums[0]
	cnt := 0
	for _, num := range nums {
		if cnt == 0 {
			current = num
			cnt++
		} else if num == current {
			cnt++
		} else {
			cnt--
		}
	}
	return current
}
