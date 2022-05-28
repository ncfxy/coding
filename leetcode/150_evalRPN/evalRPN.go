package main

import (
	"container/list"
	"strconv"
)

func evalRPN(tokens []string) int {
	var ll *list.List = list.New()
	for idx := range tokens {
		token := tokens[idx]
		if token == "+" || token == "-" || token == "*" || token == "/" {
			rightEle := ll.Back()
			ll.Remove(rightEle)
			leftEle := ll.Back()
			ll.Remove(leftEle)
			leftNum := leftEle.Value.(int)
			rightNum := rightEle.Value.(int)
			result := int(0)
			if token == "+" {
				result = leftNum + rightNum
			} else if token == "-" {
				result = leftNum - rightNum
			} else if token == "*" {
				result = leftNum * rightNum
			} else if token == "/" {
				result = leftNum / rightNum
			}
			ll.PushBack(result)
		} else {
			ll.PushBack(convertStringToInt(token))
		}
	}
	finalRes := ll.Back().Value.(int)
	return finalRes
}

func convertStringToInt(token string) int {
	res, err := strconv.ParseInt(token, 10, 64)
	if err != nil {
		return 0
	}
	return int(res)
}
