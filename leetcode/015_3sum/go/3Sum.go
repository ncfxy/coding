package main

import "sort"

func threeSum(nums []int) [][]int {
	sort.Slice(nums, func(i, j int) bool {
		return nums[i] < nums[j]
	})
	result := make([][]int, 0)
	for i := 0; i < len(nums)-2; i++ {
		if i > 0 && nums[i] == nums[i-1] {
			continue
		}
		start := i + 1
		end := len(nums) - 1
		for start < end {
			sum := nums[i] + nums[start] + nums[end]
			if sum == 0 {
				result = append(result, []int{nums[i], nums[start], nums[end]})
				for start < end && nums[start] == nums[start+1] {
					start++
				}
				start++
				for start < end && nums[end] == nums[end-1] {
					end--
				}
				end--
			} else if (nums[i] + nums[start] + nums[end]) < 0 {
				start++
			} else {
				end--
			}
		}
	}
	return result
}
