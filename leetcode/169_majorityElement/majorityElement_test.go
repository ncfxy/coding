package main

import "testing"

func TestMajorityElement(t *testing.T) {
	t.Logf("%d", majorityElement([]int{3, 2, 3}))
	t.Logf("%d", majorityElement([]int{2, 2, 1, 1, 1, 2, 2}))
}
