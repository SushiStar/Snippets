package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

/*
 * var score = 99.5
 *
 * func main_main() {
 *     sayHello("mario!")
 *
 *     for _, v := range points {
 *         println(v)
 *     }
 *     showScore()
 * }
 */

func getInput(prompt string, r *bufio.Reader) (string, error) {
	fmt.Print(prompt)

	input, err := r.ReadString('\n')

	return strings.TrimSpace(input), err
}

func createBill() bill {
	reader := bufio.NewReader(os.Stdin)

	// fmt.Println("Create a new bill name: ")
	// name, _ := reader.ReadString('\n')
	// name = strings.TrimSpace(name)
	name, _ := getInput("Create a new bill name: ", reader)

	b := newBill(name)
	fmt.Println("\nCreated a new bill - ", b.name)

	return b
}

func promptOptions(b bill) {
	reader := bufio.NewReader(os.Stdin)
	opt, _ := getInput("Choose option (a - add item, s - save bill, t - add tip): ", reader)

	switch opt {
	case "a":
		name, _ := getInput("Item name: ", reader)
		price, _ := getInput("Item price: ", reader)

		p, err := strconv.ParseFloat(price, 64)
		if err != nil {
			fmt.Println("The price must be a number")
		}
		b.addItem(name, float32(p))
		fmt.Println("item added - ", name, price)
		promptOptions(b)

	case "t":
		tip, _ := getInput("Enter tip amount ($): ", reader)
		t, err := strconv.ParseFloat(tip, 64)

		if err != nil {
			fmt.Println("The tip must be a number...")
		}
		b.updateTip(float32(t))
		fmt.Println("tip added - ", tip)
		promptOptions(b)

	case "s":
		b.save()

	default:
		fmt.Println("That was not a valid option...")
		promptOptions(b)
	}

}

func main_main() {
	/*
	 *     mybill := newBill("Mario's bill")
	 *
	 *     mybill.addItem("Onion soup", 4.50)
	 *     mybill.addItem("Fish", 12.50)
	 *     mybill.addItem("Beer", 3.50)
	 *     mybill.addItem("Veg pie", 3.25)
	 *
	 *     mybill.updateTip(4.3)
	 *     fmt.Println(mybill.format())
	 *
	 */
	mybill := createBill()
	fmt.Println(mybill.format())

	promptOptions(mybill)

}
