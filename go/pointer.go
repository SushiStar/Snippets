package main

import "fmt"

func updateNamee(x *string) {
	*x = "wedge"
}

func main_pointer() {
	name := "tifa"
	// fmt.Println("The memory address of name is", &name)

	m := &name
	fmt.Println("memory address of name is", m)
	fmt.Println("Value at memory address: ", m, "is", *m)
	updateNamee(&name)
	fmt.Println(name)
}
