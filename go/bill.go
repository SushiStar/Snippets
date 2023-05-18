package main

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
