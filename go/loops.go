package main

import "fmt"

func main_loops() {
	/*
	 * x := 0
	 * for x < 5 {
	 *     fmt.Println("The value of x is:", x)
	 *     x++
	 * }
	 */

	/*
	 * for i := 0; i < 5; i++ {
	 *     fmt.Println("The value of i is:", i)
	 * }
	 */

	// for loop
	names := []string{"mario", "luigi", "yoshi", "peach", "bowser"}
	/*
	 * for i := 0; i < len(names); i++ {
	 *     fmt.Println("The value of i is:", names[i])
	 * }
	 */

	// range-for
	/*
	 * for index, value := range names {
	 *     fmt.Printf("The value at index %v is %v\n", index, value)
	 * }
	 */

	// call by value, not reference
	for _, value := range names {
		fmt.Printf("The value is: %v\n", value)
		value = "new string"
	}
	fmt.Println(names)
}
