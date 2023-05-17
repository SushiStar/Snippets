package main

import (
	"fmt"
	"math"
)

func sayGreeting(name string) {
	fmt.Printf("Good monring %v\n", name)
}

func sayBye(name string) {
	fmt.Printf("Good bye %v\n", name)
}

func cycleNames(names []string, callee func(string)) {
	for _, name := range names {
		callee(name)
	}
}

func circleArea(radius float64) float64 {
	return math.Pi * radius * radius
}

func main_functions() {
	/*
	 * sayGreeting("mario")
	 * sayGreeting("luigi")
	 * sayBye("mario")
	 */

	// cycleNames([]string{"mario", "luigi", "peach"}, sayGreeting)
	// cycleNames([]string{"mario", "luigi", "peach"}, sayBye)
	a1 := circleArea(5.2)
	a2 := circleArea(2.2)
	// fmt.Println(a1, a2)
	fmt.Printf("%.3f %.3f\n", a1, a2)
}
