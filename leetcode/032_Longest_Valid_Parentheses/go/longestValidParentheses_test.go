package main

import "testing"

func TestLongestValidParentheses(t *testing.T) {
	t.Logf("%+v", longestValidParentheses("(()"))
	t.Logf("%+v", longestValidParentheses(")()())"))
	t.Logf("%+v", longestValidParentheses("()(()"))
	t.Logf("%+v", longestValidParentheses("()(())"))
	t.Logf("%+v", longestValidParentheses("()(()"))
	t.Logf("%+v", longestValidParentheses("()()"))
	t.Logf("%+v", longestValidParentheses("(()()"))
}
