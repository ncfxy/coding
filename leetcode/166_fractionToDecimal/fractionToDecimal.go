package main

import "fmt"

func fractionToDecimal(numerator int, denominator int) string {
	if numerator == 0 {
		return "0"
	}
	if numerator < 0 && denominator < 0 {
		return fractionToDecimal(-numerator, -denominator)
	}
	if numerator < 0 || denominator < 0 {
		return "-" + fractionToDecimal(-numerator, denominator)
	}
	result := ""
	integerPart := numerator / denominator
	result += fmt.Sprintf("%d", integerPart)
	leftInt := numerator % denominator
	if leftInt == 0 {
		return result
	}
	result += "."
	idx := 0
	leftIntMap := make(map[int]int) // 保存leftInt的位置信息
	resList := make([]int, 0)
	repeatPos := 0

	for {
		if leftInt == 0 {
			// 表示正好可以整除
			repeatPos = 9999999
			break
		}
		if pos, ok := leftIntMap[leftInt]; ok {
			repeatPos = pos
			break
		}
		leftIntMap[leftInt] = idx
		x := (leftInt * 10) / denominator
		y := (leftInt * 10) % denominator
		resList = append(resList, x)
		leftInt = y
		idx++
	}

	for i := 0; i < repeatPos && i < len(resList); i++ {
		result += fmt.Sprintf("%d", resList[i])
	}
	if repeatPos < len(resList) {
		result += "("
		for i := repeatPos; i < len(resList); i++ {
			result += fmt.Sprintf("%d", resList[i])
		}
		result += ")"
	}
	return result
}
