package main

func titleToNumber(columnTitle string) int {
	titleArray := []rune(columnTitle)
	result := 0
	for _, loc := range titleArray {
		tmp := loc - 'A' + 1
		tmpInt := int(tmp)
		result = result*26 + tmpInt
	}
	return result
}
