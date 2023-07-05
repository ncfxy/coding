package main

func longestValidParentheses(s string) int {
	var stack []int
	var max int
	stack = append(stack, -1)
	for i := 0; i < len(s); i++ {
		if s[i] == '(' {
			stack = append(stack, i)
		} else { // ')'
			stack = stack[:len(stack)-1]
			if len(stack) == 0 {
				stack = append(stack, i)
			} else {
				if i-stack[len(stack)-1] > max {
					max = i - stack[len(stack)-1]
				}
			}
		}
	}
	return max
}
