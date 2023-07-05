package main

import "fmt"

func convertToTitle(columnNumber int) string {
	alp := []rune{'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y'}
	res := ""
	for columnNumber != 0 {
		remainder := columnNumber % 26
		x := alp[remainder]
		res = fmt.Sprintf("%s%s", string(x), res)
		columnNumber = columnNumber / 26
		if remainder == 0 {
			columnNumber--
		}
	}
	return res
}
