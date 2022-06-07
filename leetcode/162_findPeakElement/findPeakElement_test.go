package main

import "testing"

func TestFindPeakElement(t *testing.T) {
	nums1 := []int{1, 2, 3, 1}
	t.Logf("%d", findPeakElement(nums1))
	nums2 := []int{1, 2, 1, 3, 5, 6, 4}
	t.Logf("%d", findPeakElement(nums2))

}
