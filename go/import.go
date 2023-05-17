package main

import (
	"fmt"
	"sort"
	"strings"
)

func main_import() {
	greeting := "Hello there friends!"

	// fmt.Println(strings.Contains(greeting, "Hello!"))
	// fmt.Println(strings.ReplaceAll(greeting, "Hello", "Hi"))

	// the original string is not modified
	// fmt.Println("original string value =", greeting)
	// fmt.Println(strings.ToUpper(greeting))
	// fmt.Println(strings.Index(greeting, "ll"))
	fmt.Println(strings.Split(greeting, " ")[0])

	ages := []int{45, 20, 35, 30, 75, 60, 50, 25}
	sort.Ints(ages)
	fmt.Println(ages)
	index := sort.SearchInts(ages, 30)
	fmt.Println(index)

	names := []string{"yoshi", "mario", "peach", "bowser", "luigi"}
	sort.Strings(names)
	fmt.Println(names)
	fmt.Println(sort.SearchStrings(names, "peach"))
}
