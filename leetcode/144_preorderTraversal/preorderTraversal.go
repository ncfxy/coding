package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func preorderTraversal(root *TreeNode) []int {
	result := make([]int, 0)
	if root == nil {
		return result
	}
	result = append(result, root.Val)
	left := preorderTraversal(root.Left)
	right := preorderTraversal(root.Right)
	result = append(result, left...)
	result = append(result, right...)
	return result
}
