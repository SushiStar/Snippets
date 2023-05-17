package main

import "fmt"

func main_loop() {
	// age := 45
	/*
	 * fmt.Println(age <= 50)
	 * fmt.Println(age >= 50)
	 * fmt.Println(age == 45)
	 * fmt.Println(age != 50)
	 */
	/*
	 *     if age < 30 {
	 *         fmt.Println("age is less than 30")
	 *     } else if age < 40 {
	 *         fmt.Println("age is less than 40")
	 *     } else {
	 *         fmt.Println("age is not less than 45")
	 *     }
	 */

	names := []string{"mario", "luigi", "yoshi", "peach", "bowser"}
	for index, value := range names {
		if index == 1 {
			fmt.Println("continuing at pos", index)
			continue
		} else if index > 2 {
			fmt.Println("Breaking at pos", index)
			break
		}
		fmt.Printf("The value at position %v is %v\n", index, value)
	}
}
