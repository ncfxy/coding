package main

import "testing"

func TestGetIntersectionNode(t *testing.T) {
	common1 := &ListNode{
		Val: 8,
		Next: &ListNode{
			Val: 4,
			Next: &ListNode{
				Val: 5,
			},
		},
	}
	headA1 := &ListNode{
		Val: 4,
		Next: &ListNode{
			Val:  1,
			Next: common1,
		},
	}
	headB1 := &ListNode{
		Val: 5,
		Next: &ListNode{
			Val: 6,
			Next: &ListNode{
				Val:  1,
				Next: common1,
			},
		},
	}
	res := getIntersectionNode(headA1, headB1)
	t.Logf("%+v", res)
}
