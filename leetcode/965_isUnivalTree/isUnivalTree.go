package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func isUnivalTree(root *TreeNode) bool {
	if root == nil {
		return true
	}
	if root.Left != nil && root.Left.Val != root.Val {
		return false
	}
	if root.Right != nil && root.Right.Val != root.Val {
		return false
	}
	leftIsUnival := isUnivalTree(root.Left)
	rightIsUnival := isUnivalTree(root.Right)
	return leftIsUnival && rightIsUnival
}
