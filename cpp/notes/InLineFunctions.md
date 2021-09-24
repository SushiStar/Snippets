# Inline functions
The **inline** keyword is used to request that the compiler treat your function as an inline function. When compiler compiles your code, all inline functions are expanded in-place -- that is, the function call is replaced with a copy of the contents of the function itself, which removes the function call overhead. The downside is that because the inline funciton is expanded in-place for *every* function call, this can make your compiled code quite a bit larger, especially if the inline function is long and/or there are many calls to the inline function.
Because of the potential for code bloat, inline functions is best suited to short functions that are typically called inside loops and do not branch.

> Be aware of inline functions, but modern compilers should inline functions for you as appropriate, so there isn't a need to use the keyword.

### Inline functions are exempt from the one-definition per program rule

> Because of the fact that inline functions do not actually result in a real function being compiled -- therefore, there's no conflict when the linker goes to link multiple files togehter.

