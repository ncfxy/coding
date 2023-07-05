package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

type BSTIterator struct {
	root           *TreeNode
	visitNodeStack []*TreeNode
	visitTagStack  []bool
	stackLen       int
}

func Constructor(root *TreeNode) BSTIterator {
	bst := BSTIterator{
		root:           root,
		visitNodeStack: make([]*TreeNode, 0),
		visitTagStack:  make([]bool, 0),
		stackLen:       0,
	}
	tmp := root
	for tmp != nil {
		bst.visitNodeStack = append(bst.visitNodeStack, tmp)
		bst.visitTagStack = append(bst.visitTagStack, false)
		bst.stackLen++
		tmp = tmp.Left
	}
	return bst
}

func (this *BSTIterator) Next() int {
	if this.stackLen == 0 {
		return 0
	}
	lastNode := this.visitNodeStack[this.stackLen-1]
	this.visitTagStack[this.stackLen-1] = true
	tmp := lastNode.Right
	for tmp != nil {
		this.visitNodeStack = append(this.visitNodeStack, tmp)
		this.visitTagStack = append(this.visitTagStack, false)
		this.stackLen++
		tmp = tmp.Left
	}
	for this.stackLen > 0 && this.visitTagStack[this.stackLen-1] {
		this.visitNodeStack = this.visitNodeStack[:this.stackLen-1]
		this.visitTagStack = this.visitTagStack[:this.stackLen-1]
		this.stackLen--
	}
	return lastNode.Val
}

func (this *BSTIterator) HasNext() bool {
	if this.stackLen > 0 {
		return true
	}
	return false
}
