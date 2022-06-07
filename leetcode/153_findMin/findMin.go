package main

func findMin(nums []int) int {
	left := 0
	last := len(nums) - 1
	right := last
	for left < right {
		mid := (left + right) >> 1
		if nums[mid] > nums[last] {
			left = mid + 1
		} else {
			right = mid
		}
	}
	return nums[left]
}
