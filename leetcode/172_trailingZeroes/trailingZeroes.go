package main

func trailingZeroes(n int) int {
	res := 0
	for n != 0 {
		n = n / 5
		res = res + n
	}
	return res
}
