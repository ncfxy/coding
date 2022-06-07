package main

import (
	"strconv"
	"strings"
)

func compareVersion(version1 string, version2 string) int {
	listV1 := strings.Split(version1, ".")
	listV2 := strings.Split(version2, ".")
	idx := 0
	for idx < len(listV1) || idx < len(listV2) {
		v1 := int64(0)
		v2 := int64(0)
		if idx < len(listV1) {
			v1, _ = strconv.ParseInt(listV1[idx], 10, 64)
		}
		if idx < len(listV2) {
			v2, _ = strconv.ParseInt(listV2[idx], 10, 64)
		}
		if v1 > v2 {
			return 1
		} else if v1 < v2 {
			return -1
		}
		idx++
	}
	return 0
}
