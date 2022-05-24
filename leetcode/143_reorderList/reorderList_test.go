package main

import "testing"

func TestReorderList(t *testing.T) {
	firstCase := &ListNode{
		Val: 1,
		Next: &ListNode{
			Val: 2,
			Next: &ListNode{
				Val: 3,
				Next: &ListNode{
					Val: 4,
				},
			},
		},
	}
	reorderList(firstCase)
	t.Logf("firstCase res: %d", firstCase.Val)

	secondCase := &ListNode{
		Val: 1,
		Next: &ListNode{
			Val: 2,
			Next: &ListNode{
				Val: 3,
				Next: &ListNode{
					Val: 4,
					Next: &ListNode{
						Val: 5,
					},
				},
			},
		},
	}
	reorderList(secondCase)
	t.Logf("secondCase res: %d", secondCase.Val)
}
