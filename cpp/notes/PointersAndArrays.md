#Pointers and arrays
Pointers and arrays are intrinsically related.
A fixed array will **decay** (be implicitly converted) into a pointer that points to the first element of the array.
It is a common fallacy in C++ to believe an array and a pointer to the array are identical. 
All elements of the array can still be accessed through the pointer, but information derived from the array's type can not be accessed from the pointer.
###Difference between pointers and fixed arrays
The primary difference occurs when using the `sizeof()` operator. When used on a fixed array, `sizeof()` returns the size of the entire array (array length \* element size). When used on a pointer, `sizeof()` returns the size of a memory address (in bytes).
A fixed array knows how long the array it is pointing to is. A pointer to the array does not.
The second difference occurs when using the address-of operator(&). Taking the address of a pointer yields the memory address of the pointer variable. Taking the address of the array returns a pointer to the enitre array. This pointer also points to the first element of the array, but the type information is different.

When pasisng an array as an argument to a function, a fixed array decays into a pointer, and the pointer is passed to the function. This means the following two functions declarations are identical:
```cpp
void printSize(int array[]);
void printSize(int *array);
```
