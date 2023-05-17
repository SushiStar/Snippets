package main

import "fmt"

func main1() {
    // print no new line added
    fmt.Print("Hello, ")
    fmt.Print("World!\n")

    // println
    fmt.Println("Hello, World!")
    age := 24
    name := "Mario"
    // fmt.Println("Hello,", name, "you are", age, "years old!")

    // formatted strings
    fmt.Printf("Hello, %v you are %v years old!\n", name, age)
    fmt.Printf("Hello, %q you are %q years old!\n", name, age)
    fmt.Printf("Age is of type %T\n", age)
    fmt.Printf("Age is of type %T\n", name)
    fmt.Printf("You scored %.2f points!\n", 225.55)

    // Sprintf (save formatted strings)
    var str = fmt.Sprintf("Hello, %q you are %d years old!", name, age)
    fmt.Println(str)
}
