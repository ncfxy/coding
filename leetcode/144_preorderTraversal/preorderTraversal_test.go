package main

import (
	"fmt"
	"testing"
)

func TestPreorderTraversal(t *testing.T) {
	root := &TreeNode{
		Val:  1,
		Left: nil,
		Right: &TreeNode{
			Val: 2,
			Left: &TreeNode{
				Val: 3,
			},
			Right: nil,
		},
	}
	result := preorderTraversal(root)
	t.Logf("root1 res: %+v", root)
	fmt.Println(result)

	var root2 *TreeNode
	result = preorderTraversal(root2)
	t.Logf("root2 res: %+v", result)
}
