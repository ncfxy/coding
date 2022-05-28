package main

func maxPoints(points [][]int) int {
	var length = len(points)
	if length == 1 {
		return 1
	}
	slope := make([][]float64, length) // 斜率
	for idx, _ := range slope {
		slope[idx] = make([]float64, length)
	}
	for idx, _ := range slope {
		for innerIdx, _ := range slope[idx] {
			slope[idx][innerIdx] = calSlope(points, idx, innerIdx)
		}
	}
	maxCount := 1
	for idx, _ := range slope {
		tmpCount := getMaxSameFloatCount(slope[idx]) + 1
		if tmpCount > maxCount {
			maxCount = tmpCount
		}
	}
	return maxCount
}

func calSlope(points [][]int, firstIdx, secondIdx int) float64 {
	firstPoint := points[firstIdx]
	secondPoint := points[secondIdx]
	if secondPoint[0] == firstPoint[0] && secondPoint[1] == firstPoint[1] {
		// 当前节点
		return -11111
	} else if secondPoint[0] == firstPoint[0] {
		// 斜率为无穷大的情况
		return -22222
	}
	slope := float64(secondPoint[1]-firstPoint[1]) / float64(secondPoint[0]-firstPoint[0])
	return slope
}

// 获取一个数组中相同数量最多的元素数量
func getMaxSameFloatCount(array []float64) int {
	m := make(map[float64]int)
	for idx, _ := range array {
		key := array[idx]
		if _, ok := m[key]; ok {
			m[key] = m[key] + 1
		} else {
			m[key] = 1
		}
	}
	maxCount := int(1)
	for _, v := range m {
		if v > maxCount {
			maxCount = v
		}
	}
	return maxCount
}
