#Refernece variables
A **reference** is a type of C++ variable that acts as an alias to another object or value.
C++ supports:
1. Reference to non-const values.
2. References to const values.
3. C++ added r-value references.

###References to non-const values
A reference (to a non-const value) is declared by using an ampersand (&) between the reference type and the variable name:
```cpp
int value{5};
int &ref{value};
```
###Reference3s as aliases
A reference acts as an alias for the object being referenced.
###l-values and r-values
In C++, variables are a type of l-value. An **l-value** is a value that has an address (in memory). Since all variables have addresses, all variables are l-values. The name l-value came about because l-values are teh only values that can be on the left side of an assignment statement.
The opposite of l-values are r-values. An r-value is an expression that is not an l-value.
> On the left side of the assignment, you must have something that represents a memory address. Everything on the right side of assignment will be evaluated to produce a value.

###References must be initialized
References must be initialized when created:
```cpp
int value{5};
int &ref{value};    // valid reference, initialized to variable value;
int &invalidRef;    // invalid, needs to reference to something
```
Unlike pointers, which can hold a null value, there is no such thing as a null reference.
References to non-const values can only be initialized with non-const l-values. They can not be initialized with const l-values or r-values.
```cpp
int x{5};
int &ref1{x};   // ok, x is an non-const l-value

const int y{7};
int &ref2{y};   // not ok, y is a const l-value

int &ref3{6};   // not ok, 6 is an r-value
```
###References cannot be reassigned
Once initialized, a reference can not be changed to reference another variable.
###References as function parameters
###Using references to pass C-style arrays to functions
```cpp
#include <iostream>
#include <iterator> 
 
// Note: You need to specify the array size in the function declaration
void printElements(int (&arr)[4])
{
  int length{ static_cast<int>(std::size(arr)) }; // we can now do this since the array won't decay
  
  for (int i{ 0 }; i < length; ++i)
  {
    std::cout << arr[i] << '\n';
  }
}
 
int main()
{
    int arr[]{ 99, 20, 14, 80 };
    
    printElements(arr);
 
    return 0;
}
```
Note that in order for this to work, you explicitly need to define the array size in the parameter.
###References as shortcuts
```cpp
int &ref{other.something.value1};
// ref can not be used in place of other.something.value1
```
###References vs pointers
Because references must be initialized to valid objects (cannot be null) and can not be changed once set, references are generally much safer to use than pointers.

##References and const
A reference to a const value is often called a **const reference** for short.

###Initialize reference to const values
References to const values can be initialized with non-const l-value, const l-values, and r-values.
```cpp
int x = 5;
const int &ref1 = x;    // okday, x is a non-const l-value

const int y = 7;
const int &ref2 = y;    // okay, y is a const l-value

const int &ref3 = 6;    // okay, 6 is an r-value
```
###References to r-values extend the lifetime of the referenced value
Normally r-values have expression scope, meaning the values are destoryed at teh end of expression in which they are created. When a reference to a const value is initialized with an r-value, the lifetime of the r-value is extended to match the lifetime of the reference.
###Const references as function parameters
References to const values are particularly useful as function parameters because of their versatility. A const reference parameter allows you to pass in a non-const l-value argument, a const l-value argument, a literal, or the result of an expression:
```cpp
#include <iostream>
 
void printIt(const int &x)
{
    std::cout << x;
}
 
int main()
{
    int a = 1;
    printIt(a); // non-const l-value
 
    const int b = 2;
    printIt(b); // const l-value
 
    printIt(3); // literal r-value
 
    printIt(2+b); // expression r-value
 
    return 0;
}
```
