package main

import (
	"fmt"
	"math"
)

type shape interface {
	area() float64
	perimeter() float64
}

type square struct {
	length float64
}

type circle struct {
	radius float64
}

func (s square) area() float64 {
	return s.length * s.length
}

func (s square) perimeter() float64 {
	return 4 * s.length
}

func (c circle) area() float64 {
	return math.Pi * c.radius * c.radius
}

func (c circle) perimeter() float64 {
	return 2 * math.Pi * c.radius
}

func printShapeInfo(s shape) {
	fmt.Printf("Area of type %T is %.3f\n", s, s.area())
	fmt.Printf("Perimeter of type %T is %.3f\n\n", s, s.perimeter())
}

func main() {
	shapes := []shape{
		square{length: 5},
		circle{radius: 3},
		circle{radius: 4.5},
		square{length: 7.8},
	}

	for _, v := range shapes {
		printShapeInfo(v)
	}
}
