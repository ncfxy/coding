package main

import (
	"encoding/json"
	"testing"
)

func TestSortList(t *testing.T) {
	case1 := &ListNode{
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
	result1 := sortList(case1)
	t.Logf("%s", ToJsonStr(result1))
}

func TestReverseList(t *testing.T) {
	case1 := &ListNode{
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
	result1 := reverseList(case1)
	t.Logf("%s", ToJsonStr(result1))
}

func ToJsonStr(obj interface{}) string {
	objBytes, _ := json.Marshal(obj)
	return string(objBytes)
}
