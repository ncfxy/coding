package main

import (
	"fmt"
	"testing"
)

func TestThreeSum(t *testing.T) {
	nums := []int{-2, 0, 0, 2, 2, -2, -2}
	result := threeSum(nums)
	fmt.Println(result)
}
