package main

type ListNode struct {
	Val  int
	Next *ListNode
}

func insertionSortList(head *ListNode) *ListNode {
	tmpHead := &ListNode{
		Val: -999999,
	}
	currentNode := head
	for currentNode != nil {
		currentNextNode := currentNode.Next
		left := tmpHead
		tmp := tmpHead.Next
		for tmp != nil {
			if currentNode.Val <= tmp.Val {
				left.Next = currentNode
				currentNode.Next = tmp
				currentNode = currentNextNode
				break
			}
			left = tmp
			tmp = tmp.Next
		}
		if tmp == nil {
			left.Next = currentNode
			currentNode.Next = nil
			currentNode = currentNextNode
		}
	}
	return tmpHead.Next
}
