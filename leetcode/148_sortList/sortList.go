package main

type ListNode struct {
	Val  int
	Next *ListNode
}

func sortList(head *ListNode) *ListNode {
	if head == nil {
		return nil
	}
	isAsc := true
	isDesc := true
	tmp := head
	for tmp.Next != nil {
		if tmp.Val > tmp.Next.Val {
			isAsc = false
		}
		if tmp.Val < tmp.Next.Val {
			isDesc = false
		}

		tmp = tmp.Next
	}
	if isAsc {
		return head
	}
	if isDesc {
		return reverseList(head)
	}

	leftHead := &ListNode{}
	rightHead := &ListNode{}
	leftTmp := leftHead
	rightTmp := rightHead
	tmp = head.Next
	for tmp != nil {
		tmpNext := tmp.Next
		if tmp.Val < head.Val {
			leftTmp.Next = tmp
			leftTmp = tmp
			leftTmp.Next = nil
		} else {
			rightTmp.Next = tmp
			rightTmp = tmp
			rightTmp.Next = nil
		}
		tmp = tmpNext
	}
	leftHead.Next = sortList(leftHead.Next)
	rightHead.Next = sortList(rightHead.Next)
	tmp = leftHead
	for tmp.Next != nil {
		tmp = tmp.Next
	}
	tmp.Next = head
	head.Next = rightHead.Next
	return leftHead.Next
}

func reverseList(head *ListNode) *ListNode {
	if head == nil || head.Next == nil {
		return head
	}
	left := head
	next := head.Next
	left.Next = nil
	newHead := next
	for next != nil {
		oldNext := next.Next
		next.Next = left
		newHead = next
		left = next
		next = oldNext
	}
	return newHead
}
