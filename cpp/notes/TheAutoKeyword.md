#The auto keyword
###The inference for initialized variables
When initializing a variable, the `auto` keyword can be used in place of `type` to tell the compiler to infer the variable's tyep from the initializer's type. This is called **type inference** (also sometimes called **type deduction**).
###Type inference for functions
In C++14, the `auto` keyword was extended to be able to deduce a function's return type from return statements in the function body. While this may seem neat, we recommed that this syntax be avoided for normal functions. The return type of a function is of great use in helping to document for the caller what a function is expected to return. When a specific type isn't specified, the caller may misinterpret what type the function will return, which can lead to inadvertant errors.
###Trailing return type synatx
The `auto` keyword can also be used to decalre functions using a **trailing return syntax**, where the return type is spedified after the rest of the function prototype.
```cpp
auto add(int x, int y) -> int
{
    return (x+y);
}
```
In the case, `auto` does not perform type inference -- it is just part of the syntax to use a trailing return type.
One nice thing is that it makes all of your function names line up.
