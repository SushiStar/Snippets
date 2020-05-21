#Function pointers
Functions have their own l-value function type -- in this case, a function type that returns an integer and takes no parameters.
Much like variables, functions live at an assigned address in memory.
###Pointers to functions
The syntax for creating a non-const function pointer is one of the ugliest things you will ever see:
```cpp
// fcnPtr is a pointer to a function that takes no arguments and returns an integer.
int (*fcnPtr)();
```
fcnPtr can point to any function that matches this type.
The parenthesis around \*fcnPtr are necessary for precedence reasons, as `int *fcnPtr()` would be interpreted as a forward declaration for a function named fcnPtr that takes no parameters and returns a pointer to an integer.
To make a const function pointer, the const goes after the asterisk:
```cpp
int (*const fcnPtr)();
```
###Assigning a function to a function pointer
Function pointers can be initialized with a function (and non-const function pointers can be assigned a function):
```cpp
int foo()
{
    return 5;
}
 
int goo()
{
    return 6;
}
 
int main()
{
    int (*fcnPtr)(){ foo }; // fcnPtr points to function foo
    fcnPtr = goo; // fcnPtr now points to function goo
 
    return 0;
}
```
One common mistake is to do this;
```cpp
fcnPtr = goo();
```
This would actually assign the return value from a call to function goo() to fcnPtr, which isn't what we want. We want fcnPtr to be assigned the address of function goo, not the return value from function goo().
Note the type of the function pointer must match the the type of the function.
```cpp
// function prototypes
int foo();
double goo();
int hoo(int x);
 
// function pointer assignments
int (*fcnPtr1)(){ foo }; // okay
int (*fcnPtr2)(){ goo }; // wrong -- return types don't match!
double (*fcnPtr4)(){ goo }; // okay
fcnPtr1 = hoo; // wrong -- fcnPtr1 has no parameters, but hoo() does
int (*fcnPtr3)(int){ hoo }; // okay
```
###Calling a function using a function pointer
There are two ways to do this:
```cpp
int foo(int x) {
    return x;
}
int main() {
    int (*fcnPtr)(int) {foo};
    (*fcnPtr)(5);
    return 0;
}

int main() {
    int (*fcnPtr)(int) {foo};
    fcnPtr(5);
    return 0;
}
```
The implicit deference method looks just like a normal function call -- which is what you'd expect.
Default parameters won't work for functions called through function pointers. Default parameters are resolved at compile time, however, function pointers are resolved at run-time.
###Passing functions as arguments to other functions
Functions used as arguments to another function are sometimes called **callback functions**.
```cpp
#include <algorithm> // for std::swap, use <utility> instead if C++11
#include <iostream>
 
// Note our user-defined comparison is the third parameter
void selectionSort(int *array, int size, bool (*comparisonFcn)(int, int))
{
    // Step through each element of the array
    for (int startIndex{ 0 }; startIndex < (size - 1); ++startIndex)
    {
        // bestIndex is the index of the smallest/largest element we've encountered so far.
        int bestIndex{ startIndex };
 
        // Look for smallest/largest element remaining in the array (starting at startIndex+1)
        for (int currentIndex{ startIndex + 1 }; currentIndex < size; ++currentIndex)
        {
            // If the current element is smaller/larger than our previously found smallest
            if (comparisonFcn(array[bestIndex], array[currentIndex])) // COMPARISON DONE HERE
                // This is the new smallest/largest number for this iteration
                bestIndex = currentIndex;
        }
 
        // Swap our start element with our smallest/largest element
        std::swap(array[startIndex], array[bestIndex]);
    }
}
 
// Here is a comparison function that sorts in ascending order
// (Note: it's exactly the same as the previous ascending() function)
bool ascending(int x, int y)
{
    return x > y; // swap if the first element is greater than the second
}
 
// Here is a comparison function that sorts in descending order
bool descending(int x, int y)
{
    return x < y; // swap if the second element is greater than the first
}
 
// This function prints out the values in the array
void printArray(int *array, int size)
{
    for (int index{ 0 }; index < size; ++index)
        std::cout << array[index] << ' ';
    std::cout << '\n';
}
 
int main()
{
    int array[9]{ 3, 7, 9, 5, 6, 1, 8, 2, 4 };
 
    // Sort the array in descending order using the descending() function
    selectionSort(array, 9, descending);
    printArray(array, 9);
 
    // Sort the array in ascending order using the ascending() function
    selectionSort(array, 9, ascending);
    printArray(array, 9);
 
    return 0;
}
```
If a function prameter is of a function type, it will be converted to a pointer to the function type. This means the following are equivalent:
```cpp
void selectionSort(int *array, int size, bool (*comparisonFcn)(int, int));
void selectionSort(int *array, int size, bool comparisonFcn(int, int));
```
This only works for function parameters, not stand-alone function pointers, and so is of somewhat limited use.

###Providing default functions
```cpp
// Default the sort to ascending sort
void selectionSort(int *array, int size, bool (*comparisonFcn)(int, int) = ascending);
```
###Making function pointers prettier with typedef or type aliases
```cpp
typedef bool (*validateFcn)(int, int);
```
This defines a typedef called `validateFcn` that is a pointer to a function that takes to ints and returns a bool.
Now instead of doing this:
```cpp
bool validate(int x, int y, bool (*fcnPtr)(int, int));  // ugly
```
You can do this:
```cpp
bool validate(int x, int y, validateFcn pfcn)       // clean
```
In C++11, you can instead use type aliases to create aliases for function pointers types:
```cpp
using validateFcn = bool(*)(int, int);      // type alias
```
This reads more naturally than the equivalent typedef, since the name of the alias and the alias definition are placed on opposite sides of the equals sign.

###Using `std::function` in C++11
To define a function pointer using this method, declare a `std::function` object like so:
```cpp
#include <functional>
bool validate(int x, int y, std::function<bool(int, int)> fcn);         // std::function method that returns a bool and takes two int parameters.


#include <functional>
#include <iostream>
int foo() {
    return 5;
}
int goo() {
    return 6;
}

int main() {
    std::function<int()> fcnPtr{foo};   // declare function pointer that returns an int and takes no parameters
    fcnPtr = goo;       // fcnPtr now points to function goo
    std::cout << fcnPtr() << '\n'; // call the function just like normal
    return 0;
}
```
Note that you can also type alias std::function:
```cpp
using validateFcnRaw = bool(*)(int, int);   // type alias to raw function pointer
using validateFcn = std::function<bool(int, int)>; // type alias to std::function
```
