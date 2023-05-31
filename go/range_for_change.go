package main

import "fmt"

func main() {
	s := []int{1, 2, 3, 4, 5}

	for _, v := range s {
		v += 1
	}
	fmt.Println(s)
}
