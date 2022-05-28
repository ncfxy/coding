package main

import "testing"

func TestMaxProduct(t *testing.T) {
	nums1 := []int{2, 3, -2, 4}
	t.Logf("%d", maxProduct(nums1))
	nums2 := []int{-2, 0, -1}
	t.Logf("%d", maxProduct(nums2))
}
