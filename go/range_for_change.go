package main

import "fmt"

func main() {
	s := []int{1, 2, 3, 4, 5}

	for i, _ := range s {
		if i == 3 {
			s[i] = 100
		}
	}
	fmt.Println(s)
}
