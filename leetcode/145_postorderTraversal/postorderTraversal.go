package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func postorderTraversal(root *TreeNode) []int {
	result := make([]int, 0)
	if root == nil {
		return result
	}
	left := postorderTraversal(root.Left)
	right := postorderTraversal(root.Right)
	result = append(result, left...)
	result = append(result, right...)
	result = append(result, root.Val)
	return result
}
