#Function overloading
Function overloading is a feature of C++ that allows us to create multiple functions with the same name, so long as they have different parameters.
```cpp
int add (int x, int y);     // integer version
int add (double x, double y); // floating point version
```
The compiler is able to determine which version of `add()` to call based on the argumentsj used in the function call.
###Function return types are not considered for uniqueness
This was an intentional choice, as it ensures the behavior of a functions call or subexpressions much simpler. As we can always determine which version of a function to be called solely on the arguments.
###Typedefs are not distinct
Since declaring a typedef does not introduce a new type, the declarations are considered identical.

Function overloading can lower a program's complexity significantly while introducing very little additional rick.
