package main

func twoSum(numbers []int, target int) []int {
	left := 0
	right := len(numbers) - 1
	result := make([]int, 2)
	for left < right {
		if numbers[left]+numbers[right] == target {
			result[0] = left + 1
			result[1] = right + 1
			return result
		} else if numbers[left]+numbers[right] > target {
			right--
		} else {
			left++
		}
	}
	return result
}
