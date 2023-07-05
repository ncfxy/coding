package main

import "testing"

func TestConvertToTitle(t *testing.T) {
	t.Logf("%s", convertToTitle(1))
	t.Logf("%s", convertToTitle(26))
	t.Logf("%s", convertToTitle(28))
	t.Logf("%s", convertToTitle(52))
	t.Logf("%s", convertToTitle(701))
	t.Logf("%s", convertToTitle(2147483647))
}
