#Pointers and const
###Pointer to const value
A pointer to a const value is a (non-const) pointer that points to a constant value.
To declare a pointer to a const value, use the `const` keyword before the data type:
```cpp
const int value = 5;
const int *ptr = &value;    // ptr is a non-const pointer that pointing to a "const int"
*ptr = 6;                   // not allowed, we can't change a const value
```
A pointer to a constant variable can point to a non-const variable.
> A pointer to a constant variable treats the variable as constant when it is accessed through the pointer, regardless of whether the variable was initially defined as const or not.
Because a pointer to a const value is not const itself, the pointer can be redirected to point at other values.

###Const pointers
A **const pointer** is a pointer whose value can not be changed after initialization.
To decalre a const pointer, use the `const` keyword between teh asterisk and the pointer name:
```cpp
int value = 5;
int *const ptr = &value;
```
Just like a normal const variable, a const pointer must be initizlized to a value upon decalaration.
However, because the value being pointed to is still non-const, it is possible to change the value being pointed to via deferencing teh const pointer.

###Const pointer to a const value
A const pointer to a const value can not be set to point to another address, nor can the value it is pointing to be changed through the pointer.
```cpp
int value = 5;
const int *const ptr = &value;
```

You only need to remember 4 rules:
1. A non-cont pointer can be redirected to point to other addresses.
2. A const pointer always points to the same address, and this address can not be changed.
3. A pointer to a non-const value can change the value it is pointing to. These cannot point to a const value.
4. A pointer to a const value treats the value as const (even if it is not), and thus can not change the value it is pointing to.
