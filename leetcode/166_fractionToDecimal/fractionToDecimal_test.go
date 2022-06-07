package main

import "testing"

func TestFractionToDecimal(t *testing.T) {
	t.Logf("%s", fractionToDecimal(1, 2))
	t.Logf("%s", fractionToDecimal(2, 1))
	t.Logf("%s", fractionToDecimal(4, 333))
	t.Logf("%s", fractionToDecimal(-50, 8))
}
