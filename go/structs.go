package main

import "fmt"

func main_struct() {
	mybill := newBill("mario's bill")
	// fmt.Println(mybill)

	fmt.Println(mybill.format())

	mybill.updateTip(10)
	// fmt.Println(mybill.format())

	mybill.addItem("onion soup", 4.50)
	fmt.Println(mybill.format())
}
