package main

import (
	"fmt"
	"os"
)

type bill struct {
	name  string
	items map[string]float32
	tip   float32
}

// make new bills
func newBill(name string) bill {
	b := bill{
		name:  name,
		items: map[string]float32{},
		tip:   0,
	}
	return b
}

// format the bill
// receiver b
// can only be called from a bill object, still takes a copy
func (b bill) format() string {
	fs := "Bill breakdown: \n"
	var total float32 = 0

	for k, v := range b.items {
		fs += fmt.Sprintf("%-25v ...$%.2f \n", k+":", v)
		total += v
	}
	// tip
	fs += fmt.Sprintf("-----\n%-25v ...$%0.2f \n", "tip:", b.tip)

	// total
	fs += fmt.Sprintf("%-25v ...$%0.2f \n", "total:", total+b.tip)
	return fs
}

// update the tip
// if a pointer is passed, in the receiver, Go will automatically deference it
func (b *bill) updateTip(tip float32) {
	b.tip = tip
}

// add an item to the bill

func (b *bill) addItem(name string, price float32) {
	b.items[name] = price
}

func (b *bill) save() {
	data := []byte(b.format())
	err := os.WriteFile("bills/"+b.name+".txt", data, 0644)
	if err != nil {
		panic(err)
	}
	fmt.Println("Bill was saved to file")
}
