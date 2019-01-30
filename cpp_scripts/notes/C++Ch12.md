# Chapter 12:Functions

## Function Declarations
- The semantics of argument passing are identical to the semantics of copy initialization.
    Argument types are checked and implicit argument type conversion takes place when necessary.
- The most basic advice is to keep a function of a size so that you can look at it in total on a screen.(40 lines on a function);
- virtual: indicating that it can be overridden in a derived class.
    override: indicating that it must be overriding a virtual function from a base class.
    static: inidicating that it is not associated with a particular object.
- A function called itself is said to be recursive.
- ***Each time a function is called, a new copy of its argument and local (automatic) variables is created. The store is reused after the function returns, so a pointer ot a local non-static variable should never be returned.***
- A function that does not return normally can be marked as <code>[[noreturn]]</code>
- A constexpr function consist of a single return-statement; no loops and no local variables are allowed.
- If a local variable is declared ***static***, a single, statically allocated object will be used to represent that variable in all calls of the function.

## Argument passing
- Declaring a pointer argument const tells readers that the value of an object pointed to by that argument is not changed by the function.
- Rules of passing arguments:
    * Use pass-by-value for small objects.
    * Use pass-by-const-reference to pass large values that you don't need to modify.
    * Return a result as a return value rather than modifying an object through an argument.
    * Use rvalue references to implement move and forwarding.
    * Pass a pointer if "no object" is a valid alternative.
    * Use pass-by-reference only if you have to.
## Overloaded Functions
- Overload resolution is independent of the order of declaration of the functions considered.
- Return types are not considered in overload resolution.
- Functions declared in different non-namespace scope do not overload.
## Pre- and Postconditions
The writer of a function has several alternatives, including:
* Make sure that every input has a valid result (so that we don't have a precondition).
* Assume that the precondition holds (rely on the caller not to make mistakes).
* Check that the precondition holds and throw an exception if it does not.
* Check that the precondition holds and terminate the program if it does not.
## Pointer to function
* Pointers to functions have argument types declared just like the functions themselves.
* There's no implicit conversions of argument or return type when pointers to functions are assigned or initialized.
## Macros
* The first rule about macros is: don't use them unless you have to.
* Macro names cannot be overloaded.
* The macro processor cannot handle recursive calls.
