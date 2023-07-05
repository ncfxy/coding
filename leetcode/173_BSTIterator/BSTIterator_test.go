package main

import "testing"

func TestBSTIterator(t *testing.T) {
	root := &TreeNode{
		Val: 7,
		Left: &TreeNode{
			Val: 3,
		},
		Right: &TreeNode{
			Val: 15,
			Left: &TreeNode{
				Val: 9,
			},
			Right: &TreeNode{
				Val: 20,
			},
		},
	}
	obj := Constructor(root)
	t.Logf("%d", obj.Next())
	t.Logf("%d", obj.Next())
	t.Logf("%t", obj.HasNext())
	t.Logf("%d", obj.Next())
	t.Logf("%t", obj.HasNext())
	t.Logf("%d", obj.Next())
	t.Logf("%t", obj.HasNext())
	t.Logf("%d", obj.Next())
	t.Logf("%t", obj.HasNext())
}

// bSTIterator.next();    // 返回 3
// bSTIterator.next();    // 返回 7
// bSTIterator.hasNext(); // 返回 True
// bSTIterator.next();    // 返回 9
// bSTIterator.hasNext(); // 返回 True
// bSTIterator.next();    // 返回 15
// bSTIterator.hasNext(); // 返回 True
// bSTIterator.next();    // 返回 20
// bSTIterator.hasNext(); // 返回 False
