/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
package main

type ListNode struct {
	Val  int
	Next *ListNode
}

func reorderList(head *ListNode) {
	if head == nil || head.Next == nil {
		return
	}
	// 通过快慢指针找到后一半的启始点
	var slowLeft *ListNode
	slow := head
	quick := head
	for quick != nil {
		slowLeft = slow
		slow = slow.Next
		quick = quick.Next
		if quick != nil {
			quick = quick.Next
		}
	}
	// slow就是后一半的起始点,对后一半链表进行反转
	slowLeft.Next = nil
	slowLeft = nil
	for slow != nil {
		slowNext := slow.Next
		slow.Next = slowLeft
		slowLeft = slow
		slow = slowNext
	}
	// slowLeft就是后一半新的head，将后一半插入到前一半的间隔中去
	firstHalf := head
	secondHalf := slowLeft
	for firstHalf != nil && secondHalf != nil {
		firstNext := firstHalf.Next
		secondNext := secondHalf.Next
		firstHalf.Next = secondHalf
		secondHalf.Next = firstNext
		firstHalf = firstNext
		secondHalf = secondNext
	}
}
