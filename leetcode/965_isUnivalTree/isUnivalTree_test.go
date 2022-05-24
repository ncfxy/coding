package main

import "testing"

func TestIsUnivalTree(t *testing.T) {
	root1 := &TreeNode{
		Val: 1,
		Left: &TreeNode{
			Val: 1,
			Left: &TreeNode{
				Val: 1,
			},
			Right: &TreeNode{
				Val: 1,
			},
		},
		Right: &TreeNode{
			Val: 1,
			Right: &TreeNode{
				Val: 1,
			},
		},
	}
	t.Logf("root1 is %t", isUnivalTree(root1))
	root2 := &TreeNode{
		Val: 2,
		Left: &TreeNode{
			Val: 2,
			Left: &TreeNode{
				Val: 5,
			},
		},
		Right: &TreeNode{
			Val: 2,
		},
	}
	t.Logf("root2 is %t", isUnivalTree(root2))
}
