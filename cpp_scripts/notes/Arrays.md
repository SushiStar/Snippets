#Arrays
A **fixed array** (also called a **fixed length array** or **fixed size array**) is an array where the length is known at compile time.
When declaring a fixed array, the length of the array (between the square brackets) must be a compile-time constant. This is because the length of a fixed array must be known at compile time:
```cpp
// using a literal constant
int array[5]; // Ok
 
// using a macro symbolic constant
#define ARRAY_LENGTH 5
int array[ARRAY_LENGTH]; // Syntactically okay, but don't do this
 
// using a symbolic constant
const int arrayLength = 5;
int array[arrayLength]; // Ok
 
// using an enumerator
enum ArrayElements
{
    MAX_ARRAY_LENGTH = 5
};
int array[MAX_ARRAY_LENGTH]; // Ok
```
Note that non-const variables or run-time constants cannot be used.

####A note on dynamic arrays
Because fixed arrays have memory allocated at compile time, that introduces two limitations:
    * Fixed arrays cannot have a length based on either user input or some other value calculated at runtime.
    * Fixed arrays have a fixed length that can not be changed.

###Initizlizing fixed arrays
C++ provides a more conventient way to initialize entire arrays via use of an **initilizer list**.
```cpp
int prime[5] = {2, 3, 5, 7, 11};
```
If there are more initizlizers in the list than the array can hold, the compiler will generate an error.
However, if there are less initializers in the list than the array can hold, the remaining elements are initizlied to 0 (or whatever value 0 converts to for a non-integral fundamental type -- e.g. 0.0 for double). This is called **zero initizlization**.
###Omitted length
If you are initializing a fixed array of elements using an initializer list, the compiler can figure out the length of the array for you, and you can explicitly declaring the length of the array.
###Arrays and enums
```cpp
enum StudentNames
{
    KENNY, // 0
    KYLE, // 1
    STAN, // 2
    BUTTERS, // 3
    CARTMAN, // 4
    WENDY, // 5
    MAX_STUDENTS // 6
};
 
int main()
{
    int testScores[MAX_STUDENTS]; // allocate 6 integers
    testScores[STAN] = 76; // still works
 
    return 0;
}
```
Enum classes don't have an implicit conversion to integer, so if you use enum classes enumerators as array indices you will get a compiler error.
