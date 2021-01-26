#Sorting an array using selection sort
###How sorting works
Sorting is generally performed by repeatedly comparing paris of array elements, and swapping them if they meet some predefined criteira. The order in which these elements are compared differs depending on which sorting algorithm is used.
###Selection sort
Selection sort performs the following steps to sort an array from smallest to largest:
1. Starting at array index 0, search the entire array to find the smallest value.
2. Swap the smallest value found in the array with the value at index 0.
3. Repeat steps 1&2 starting from the next index.

##Multidimensional Arrays
###Initializing two-dimension arrays
To initialize a two-timensional array, it is easiest to use nested braces, with each set of numbers representing a row:
```cpp
int array[3][5]
{
  { 1, 2, 3, 4, 5 }, // row 0
  { 6, 7, 8, 9, 10 }, // row 1
  { 11, 12, 13, 14, 15 } // row 2
};
```
Just likek normal arrays, multidimensional arrays can still be initialized to 0 as follows:
```cpp
int array[3][5]{};
```
###Multidimensional arrays larger than two dimensions
Multidimensional arrays may be alrger than two dimensions. It's typically better to initialize the array to 0 and explicitly assign values using nested loops.
