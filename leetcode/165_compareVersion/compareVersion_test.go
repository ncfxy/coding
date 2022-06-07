package main

import "testing"

func TestCompareVersion(t *testing.T) {
	t.Logf("res1: %d", compareVersion("1.01", "1.001"))
	t.Logf("res2: %d", compareVersion("1.0", "1.0.0"))
	t.Logf("res3: %d", compareVersion("0.1", "1.1"))
}
