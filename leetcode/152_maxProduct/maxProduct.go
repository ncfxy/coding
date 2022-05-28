package main

// 先正向遍历求最大，再反向遍历求最大，主要是处理选几个负数
func maxProduct(nums []int) int {
	maxResult := nums[0]
	current := 1
	for idx := range nums {
		if current == 0 {
			current = nums[idx]
		} else {
			current = current * nums[idx]
		}
		if current > maxResult {
			maxResult = current
		}
	}
	current = 1
	for idx := len(nums) - 1; idx >= 0; idx-- {
		if current == 0 {
			current = nums[idx]
		} else {
			current = current * nums[idx]
		}
		if current > maxResult {
			maxResult = current
		}
	}
	return maxResult
}
