package main

import "fmt"

func main1() {
    // array
	// var ages [3]int = [3]int{20, 25, 30}
    var ages = [3]int{20, 25, 30}

    names := [4]string{"Yoshi", "Mario", "Peach", "Bowser"}
    names[1] = "Luigi"

    fmt.Println(ages, len(ages))
    fmt.Println(names, len(names))

    // slices (use arrays under the hood)
    // but we can manipulate them more easily
    var scores = []float32{100, 50, 60}
    scores[2] = 25
    scores = append(scores, 85)
    fmt.Println(scores, len(scores))

    // slice ranges
    rangeOne := names[1:4]
    fmt.Println(rangeOne)

    rangeTwo := names[2:]
    fmt.Println(rangeTwo)

    rangeOne = append(rangeOne, "koopa")
    fmt.Println(rangeOne)
}
