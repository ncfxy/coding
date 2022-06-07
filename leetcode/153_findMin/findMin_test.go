package main

import "testing"

func TestFindMin(t *testing.T) {
	nums1 := []int{3, 4, 5, 1, 2}
	t.Logf("%d", findMin(nums1))
	nums2 := []int{4, 5, 6, 7, 0, 1, 2}
	t.Logf("%d", findMin(nums2))
	nums3 := []int{11, 13, 15, 17}
	t.Logf("%d", findMin(nums3))
}
