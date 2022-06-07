package main

import "testing"

func TestMaximumGap(t *testing.T) {
	nums1 := []int{3, 6, 9, 1}
	t.Logf("res1: %d", maximumGap(nums1))
	nums2 := []int{10}
	t.Logf("res1: %d", maximumGap(nums2))
	nums3 := []int{32, 65, 19, 100}
	t.Logf("res1: %d", maximumGap(nums3))
}
