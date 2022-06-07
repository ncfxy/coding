package main

func maximumGap(nums []int) int {
	if len(nums) < 2 {
		return 0
	}
	maxLength := 0
	for i := 0; i < len(nums); i++ {
		length := getNumLength(nums[i])
		if length > maxLength {
			maxLength = length
		}
	}
	for i := 0; i < maxLength; i++ {
		// 从最低位到最高位遍历
		tmp := make([][]int, 10)
		for j := 0; j < len(nums); j++ {
			posNum := getPosNum(nums[j], i)
			tmp[posNum] = append(tmp[posNum], nums[j])
		}
		idx := 0
		for j := 0; j < 10; j++ {
			for k := 0; k < len(tmp[j]); k++ {
				nums[idx] = tmp[j][k]
				idx++
			}
		}
	}
	res := 0
	for i := 1; i < len(nums); i++ {
		diff := nums[i] - nums[i-1]
		if diff > res {
			res = diff
		}
	}
	return res
}

func getPosNum(num int, pos int) int {
	for i := 0; i < pos; i++ {
		num = num / 10
	}
	return num % 10
}

func getNumLength(num int) int {
	length := 0
	for num != 0 {
		length++
		num = num / 10
	}
	return length
}
