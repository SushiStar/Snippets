package main

import "fmt"

func main_map() {
	menu := map[string]float64{
		"soup":           4.99,
		"pie":            7.99,
		"salad":          6.99,
		"toffee pudding": 3.55,
	}
	fmt.Println(menu)
	fmt.Println("The price of pie is:", menu["pie"])

	// looping maps
	for k, v := range menu {
		fmt.Println("The price of", k, "is", v)
	}

	phonebook := map[int]string{
		267584967: "mario",
		984759373: "luigi",
		845775485: "peach",
	}
	fmt.Println(phonebook)
	fmt.Println(phonebook[267584967])

	phonebook[984759373] = "bowser"
	fmt.Println(phonebook)
}
