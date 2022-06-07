package main

import "testing"

func TestMinStack(t *testing.T) {
	minStack := Constructor()
	minStack.Push(-2)
	minStack.Push(0)
	minStack.Push(-3)
	t.Logf("%d", minStack.GetMin())
	minStack.Pop()
	t.Logf("%d", minStack.Top())
	t.Logf("%d", minStack.GetMin())
}
