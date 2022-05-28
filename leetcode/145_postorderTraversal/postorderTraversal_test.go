package main

import (
	"encoding/json"
	"testing"
)

func TestPostorderTraversal(t *testing.T) {
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
	result := postorderTraversal(root)
	t.Logf("root1 res: %+v", result)

	var root2 *TreeNode
	result = postorderTraversal(root2)
	t.Logf("root2 res: %+v", result)

	treeByte, _ := json.Marshal(root)
	treeStr := string(treeByte)
	t.Logf("%s", treeStr)
}
