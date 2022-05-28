package main

import "testing"

func TestMaxPoints(t *testing.T) {
	points1 := [][]int{
		{1, 1},
		{2, 2},
		{3, 3},
	}
	t.Logf("%d", maxPoints(points1))
	points2 := [][]int{
		{1, 1},
		{3, 2},
		{5, 3},
		{4, 1},
		{2, 3},
		{1, 4},
	}
	t.Logf("%d", maxPoints(points2))
}
