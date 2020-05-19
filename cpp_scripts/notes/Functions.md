#Functions 
##Function parameters and arguments
###Parameters vs Arguments
A **function parameter** is a variable declared in the function declaration.
An **argument** is the value that is passed to the function by the caller;
When a function is called, all of the prameters of the function are created as variables, and the value of the arguments are copied into the parameters. Althought parameters are not declared inside the function block, function parameters have local scope.
##Passing arguments by value
###Pros and cons of pass by value
Pros:
    - Arguments passed by value can be variables, literals, expressions, structs & classes ...
Cons:
    - Copying structs and classes can incur a significant performance penalty, especialy if the function is called many times.
When to use pass by value:
    - When passing fundamental data type and enumerators, and the function does not need to change the argument.
When not to use pass by value:
    - When passing structs or classes.
##Passing argument by reference
To pass a variable by reference, we simply declare the function parameters as references rather than as normal variables.
###Returning  multiple values via out parameters
Pameters that only used for returning values back to the caller are called **out parameters**. By convention, output parameters are typically the rightmost parameters.
####Limitations of pass by reference
Non-const references can only reference non-const l-values, so a reference parameter cannot accept an argument that is a const l-value or an r-value.
###Pass by const reference
Using const is useful for several reasons:
    - It enlists the compilers help in ensuring values that shouldn't be changed aren't changed.
    - It tells the programmer that the function won't change the value of the argument.
    - You can't pass a const argument to a non-const reference parameter. Using const parameters ensures you can pass both non-const and const arguments to the function.
    - Const references can accept any type of argument, including non-const l-values, const l-values, and r-values.
>**Rule**
> When passing an argument by reference, always use a const reference unless you need to change the value of the argument.
> Non-const references cannot bind to r-values. A function with a non-const reference parameter cannot be called with literals or temporaries.
###References to pointers
It's possible to pass a pointer by reference, and have the function change the address of the pointer entirely.
As a reminder, you can pass a C-style array by reference. This is useful if you need the ability for the function to change the array or you need access to the array's type information of a fixed array. However, note that in order for this to work, you explicitly need to define the array size in the parameter.
```cpp
#include <iostream>
 
// Note: You need to specify the array size in the function declaration
void printElements(int (&arr)[4])
{
  int length{ sizeof(arr) / sizeof(arr[0]) }; // we can now do this since the array won't decay
  
  for (int i{ 0 }; i < length; ++i)
  {
    std::cout << arr[i] << std::endl;
  }
}
 
int main()
{
    int arr[]{ 99, 20, 14, 80 };
    
    printElements(arr);
 
    return 0;
}
```
This means this only works with fixed arrays of one particular length. If you wnat this to work with fixed arrays of any length, you can make the array length a template parameter.
###Pros and cons of pass by reference
Pros:
    - References allow a function to change the value of the argument. Const references can be used to guarantee the function won't chagne the arguemnt.
    - Because a copy of the argument is not made, pass by reference is fast, even when used with large structs or classes.
    - References can be used to return multiple values from a function.
    - References must be initialized, so there's no worry about null value.
Cons:
    - Because a non-const reference cannot be initialized with a const l-value or an r-value, arguments to non-const reference parameters must be normal variables.
    - It can be hard to tell whether an argument passed by non-const reference is meant to be input, output or both. Judicious use of const and a naming suffix for out variables can help.
    - It's impossible to tell from the function call whether the argument may change. An argument passed by value and passed by reference looks the same.

##Passing arguments by address
Passing an argument by address involves passing the address of the argument variable rather than the argument variable itself.
###Addresses are actually passed by value
- When passing an argument by address, the function parameter variable receives a copy of the address from the argument. At this point, the function parameter and the argument both point to teh same value.
- If the function parameter is then deferenced to change the value being pointed to, that will impact the value the argument is pointing to, since both the function parameter and argument are pointing to the same value.
- If the function parameter is assigned a different address, that will not impact the argument.
