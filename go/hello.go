package main

import "fmt"

func main_hello() {
	fmt.Println("Hello, World!")

	/*
	 *
	 *
	 *     // strings
	 *     var nameOne string = "Mario"
	 *     fmt.Println("Hello,", nameOne)
	 *
	 *     // if no type is specified, Go will infer it
	 *     var nameTwo = "Luigi"
	 *     fmt.Println("Hello,", nameTwo)
	 *
	 *     var nameThree string
	 *     fmt.Println("Hello,", nameThree) // empty string
	 *
	 *     nameOne = "Peach"
	 *     nameThree = nameOne
	 *     nameOne = "Bowser"
	 *     fmt.Println("Hello,", nameOne)
	 *     fmt.Println("Hello,", nameThree)
	 *
	 *     // for initialization only, later on assignment won't involve ':'
	 *     // cannot do this inside a function either
	 *     nameFour := "Yoshi"
	 *     fmt.Println("Hello,", nameFour)
	 *
	 *     // integers
	 *     var ageOne int = 20
	 *     var ageTwo = 30
	 *     ageThree := 40
	 *
	 *     fmt.Println(ageOne, ageTwo, ageThree)
	 */

	// bits and memory
	/*
	 *  var numOne int8 = 22
	 *  var numTwo uint8 = -128
	 *  var numThree int16 = 256
	 *  fmt.Println(numOne, numTwo, numThree)
	 *
	 */

	// floats
	var scoreOne float32 = 25.98
	scoreTwo := 2345894899828342454786839425.980980980
	fmt.Println(scoreOne, scoreTwo)
}
