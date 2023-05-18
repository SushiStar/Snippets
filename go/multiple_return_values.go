package main

import (
	"fmt"
	"strings"
)

func getInitials(n string) (string, string) {
	s := strings.ToUpper(n)
	names := strings.Split(s, " ")
	var initialis []string
	for _, v := range names {
		initialis = append(initialis, v[:1])
	}
	if len(initialis) > 1 {
		return initialis[0], initialis[1]
	}
	return initialis[0], "_"
}

func main_mrv() {
	fn1, sn1 := getInitials("tifa lokhart")
	fmt.Println(fn1, sn1)

	fn2, sn2 := getInitials("cloud strife")
	fmt.Println(fn2, sn2)

	fn3, sn3 := getInitials("barret")
	fmt.Println(fn3, sn3)
}
