package main

import "testing"

func TestTwoSum(t *testing.T) {
	t.Logf("%+v", twoSum([]int{2, 7, 11, 15}, 9))
	t.Logf("%+v", twoSum([]int{2, 3, 4}, 6))
	t.Logf("%+v", twoSum([]int{-1, 0}, -1))
}
