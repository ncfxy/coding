package main

import (
	"fmt"
	"testing"
)

func Test_TwoSum(t *testing.T) {
	fmt.Println("Hello, 世界")
	a := []int{2, 7, 11, 15}
	t := 9
	result := twoSum(a, t)
	fmt.Println(result)
	a = []int{3, 2, 4}
	t = 6
	result = twoSum(a, t)
	fmt.Println(result)
}
