package main

import "testing"

func TestConvertStringToInt(t *testing.T) {
	input := "11"
	t.Logf("%d", convertStringToInt(input))
	input2 := "-11"
	t.Logf("%d", convertStringToInt(input2))
}

func TestEvalRPN(t *testing.T) {
	tokens1 := []string{"2", "1", "+", "3", "*"}
	t.Logf("%d", evalRPN(tokens1))
	tokens2 := []string{"4", "13", "5", "/", "+"}
	t.Logf("%d", evalRPN(tokens2))
	tokens3 := []string{"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"}
	t.Logf("%d", evalRPN(tokens3))
}
