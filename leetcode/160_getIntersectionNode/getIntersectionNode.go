package main

type ListNode struct {
	Val  int
	Next *ListNode
}

func getIntersectionNode(headA, headB *ListNode) *ListNode {
	lenA := 0
	lenB := 0
	tmpA := headA
	for tmpA != nil {
		tmpA = tmpA.Next
		lenA++
	}
	tmpB := headB
	for tmpB != nil {
		tmpB = tmpB.Next
		lenB++
	}
	tmpA = headA
	tmpB = headB
	for lenA > lenB {
		tmpA = tmpA.Next
		lenA--
	}
	for lenB > lenA {
		tmpB = tmpB.Next
		lenB--
	}
	for tmpA != nil && tmpB != nil {
		if tmpA == tmpB {
			return tmpA
		}
		tmpA = tmpA.Next
		tmpB = tmpB.Next
	}
	return nil
}
