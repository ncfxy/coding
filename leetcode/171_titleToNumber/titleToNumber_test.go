package main

import "testing"

func TestTitleToNumber(t *testing.T) {
	t.Logf("%d", titleToNumber("A"))
	t.Logf("%d", titleToNumber("AB"))
	t.Logf("%d", titleToNumber("ZY"))
}
