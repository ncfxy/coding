package main

import (
	"fmt"
)

func main() {
	var N int
	var str string
	fmt.Scanf("%d", &N)
	fmt.Scanf("%s", &str)
	fmt.Println(N)
	fmt.Println(str)
	fmt.Println(str[0:2])
	fmt.Println(str[0])
	fmt.Println('B' - 'A')
	fmt.Println('A' - 'a')
}
