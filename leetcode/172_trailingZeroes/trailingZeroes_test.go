package main

import "testing"

func TestTrailingZeroes(t *testing.T) {
	t.Logf("%d", trailingZeroes(3))
	t.Logf("%d", trailingZeroes(5))
	t.Logf("%d", trailingZeroes(10))
}
