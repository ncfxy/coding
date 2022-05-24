package main

import "testing"

func TestInsertionSortList(t *testing.T) {
	firstCase := &ListNode{
		Val: 4,
		Next: &ListNode{
			Val: 2,
			Next: &ListNode{
				Val: 1,
				Next: &ListNode{
					Val: 3,
				},
			},
		},
	}
	firstCaseResult := insertionSortList(firstCase)
	t.Logf("firstCaseHead: %d", firstCaseResult.Val)

	secondCase := &ListNode{
		Val: -1,
		Next: &ListNode{
			Val: 5,
			Next: &ListNode{
				Val: 3,
				Next: &ListNode{
					Val: 4,
					Next: &ListNode{
						Val: 0,
					},
				},
			},
		},
	}
	secondCaseResult := insertionSortList(secondCase)
	t.Logf("secondCaseHead: %d", secondCaseResult.Val)
}
