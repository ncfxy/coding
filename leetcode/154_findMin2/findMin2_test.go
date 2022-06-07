package main

import "testing"

func TestFindMin(t *testing.T) {
	nums1 := []int{1, 3, 5}
	t.Logf("%d", findMin(nums1))
	nums2 := []int{2, 2, 2, 0, 1}
	t.Logf("%d", findMin(nums2))
	nums3 := []int{3, 1, 3}
	t.Logf("%d", findMin(nums3))
}
