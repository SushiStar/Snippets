package main

import "fmt"

// groupA: strings ints floats booleans arrays structs
// groupB: slices maps functions

// takes a copy of the variable
func updateName(x string) string {
	x = "wedge"
	return x
}

func updateMenu(y map[string]float64) {
	y["coffee"] = 2.99
}

func main_pbv() {
	name := "tifa"

	name = updateName(name)

	// fmt.Println(name)

	menu := map[string]float64{
		"soup":   4.99,
		"pie":    7.99,
		"coffee": 3.99,
	}

	updateMenu(menu)
	fmt.Println(menu)
}
