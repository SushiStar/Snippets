#Introduction to pointers
###The address-of operator (&)
The address-of operator (&) allows us to see what memory address is assigned to variable.
### The deference operator(\*)
The deference operator(\*) allows us to acccess the value at a particular address;
###Pointers
A pointer is a variable that  holds a memory address at its values.
###Declaring a pointer
Pointer variables are declared just like normal variables, only with an asterisk between the data type and the variable name.
Syntatically, C++ will accept the asterisk next to the data type, next to the variable name, or even in the middle.
>**Best practice**
>When declaring a pointer variable, put the asterisk nest to the variable name.
>When returning a pointer from a function, it's clear to put the asterisk next to the return type.
###The address-of operator returns a pointer.
It's worth noting that the address-of operator (&) doesn't return the address of its operand as a literal. Instead, it returns a pointer containing the address of the operand.
###Deferencing pointers
A deferenced pointer evaluates to the contents of the address it is pointing to.

## Null pointers
### Null values and null pointers
Pointers are not initizlized when they are instantiated. Unless a value is assigned, a pointer will point to some garbage address by default.
A **null value** is a special value that means the pointer is not pointing at anything.
###The NULL macro
In C++, there is a special preprocessor macro called NULL (defiend in the `<cstddef>`). The macro is inherited form C, where it is commonly used to indicate a null pointer.
###The perils of using 0 (or NULL) for null pointers
In the likely case wher NULL is defined as value 0, print(NULL) will call print(int), not print(int\*) like you might expect for a null pointer literal.
###nullptr in C++11
C++ will implicitly convert nullptr to any pointer type.
C++ also introduces a new type called `std::nullptr_t` (in header <cstddef>). `std::nullptr_t` can only hold one value: `nullptr`.
