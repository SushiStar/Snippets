#Template classes
In order for the compiler to use a template, it must see both the template definition (not just a declaration) and the template type used to instantiate the template. Also remember that C++ compiles files individually.

When the `Array.h` header is #included in main, the template class definition is copied into `main.cpp`.
When the compiler sees that we need two template instances, `Array<int>`, and `Array<double>`, it will instantiate these, and compile them as part of `main.cpp`.
However, when it gets around to compiling Array.cpp separately, it will have forgotten that we need an `Array<int>` and `Array<double>`, so that template function is never instantiated.
Thus, we get a linker error, because the compiler can’t find a definition for `Array<int>::getLength()` or `Array<double>::getLength()`.

The easiest way is to simply put all of your template class code in the header file (in this case, put the contents of `Array.cpp` into `Array.h`, below the class).
In this way, when you `#include` the header, all of the template code will be in one place. The upside of this solution is that it is simple. The downside here is that if the template class is used in many places, you will end up with many local copies of the template class, which can increase your compile and link times (your linker should remove the duplicate definitions, so it shouldn’t bloat your executable). This is our preferred solution unless the compile or link times start to become a problem.

If you feel that putting the `Array.cpp` code into the `Array.h` header makes the header too long/messy, an alternative is to rename `Array.cpp` to `Array.inl` (.inl stands for inline), and then include Array.inl from the bottom of the Array.h header. That yields the same result as putting all the code in the header, but helps keep things a little cleaner.

Another alternative is to use a three-file approach. The template class definition goes in the header. The template class member functions goes in the code file. Then you add a third file, which contains all of the instantiated classes you need:
```cpp
// Ensure the full Array template definition can be seen
#include "Array.h"
#include "Array.cpp" // we're breaking best practices here, but only in this one place

// #include other .h and .cpp template definitions you need here

template class Array<int>; // Explicitly instantiate template Array<int>
template class Array<double>; // Explicitly instantiate template Array<double>

// instantiate other templates here
```
The "template class" command causes the compiler to explicitly instantiate the template class. In the above case, the compiler will stencil out both `Array<int>` and `Array<double>` inside of `templates.cpp`.
Because `templates.cpp` is inside our project, this will then be compiled. These functions can then be linked to from elsewhere.
