#Returning values by value, reference, and address
###Return by value
When to use return by value:
- When returning variables that were declared inside the function
- When returning function arguments that were passed by value
When not to use return by value:
- When returning a built-in array or pointer
- When returning a large struct or class
###Return by address
Returning by address involves returning the address of a variable to the caller.
If you try to return the address of a variable local to the function, your program will exhibit undefined behavior.The value is destroyed just after its address is returned to the caller. Return by address was often used to return dynamically allocated memory to the caller. Smart pointers and types that clean up after themselves should be used instead of manual allocations.
When to use return by address:
    - When returning dynamically allocated memory and you can't use a type that handles allocations for you.
    - When returning function arguments that were passed by address.
When not to use return by address:
    - When returning variables that were declared inside the function or parameters that were passed by value (use return by value)
    - When returning a large struct  or class that was passed by reference (use return by reference)
###Return by reference
Similar to pass by address, values returned by reference must be variables (you should not return a reference to a literal or an expression that resolves to a temporary value, as those will go out of scope at the end of the function and you'll end up returning a dangling reference). When a variable is returned by reference, a reference to the variable is passed back to the caller.
Return by reference is typically used to return arguments passed by reference to the function back to the caller.
When to use return by reference:
    - When returning a reference parameter.
    - When returning an element from an array that was passed into the function.
    - When returning a large struct or class that will not be destroyed at the end of the function.
When not to use return by reference:
    - When returning variables that were declared inside the function or parameters that were passed by values.
    - When returning a built-in array or pointer value.
>Lifetime extension doesn't save dangling references.
> ```cpp
>   const int& returnByReference() {
>       return 5;
>   }
>   int main() {
>       const int &ref {returnByReference()};   // runtime error
>   }
> ```
