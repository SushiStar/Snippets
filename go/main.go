package main

import (
	"bufio"
	"fmt"
	"os"
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

	fmt.Println(opt)
}

func main() {
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
