#Global constants and inline variables
> We use const instead of constexpr in this method because constexpr variables can't be forward decalred, even if they have external linkage.

###Global constants as inline variables
C++17 introduced a new concept called `inline variables`. In C++, the term `inline` has evolved to mean "multiple definitions are allowed". Thus an **inline variable** is one that is allowed to be defined in multiple files without violating the one definition rule. Inline global variables have external linkage by default.

Inline variables have two primary restrictions that must be obeyed:
1. All definitions of the inline variable must be identical (otherwise, undefined behavior will result).
2. The inline variable definition (not a forward declaration) must be present in any file that uses the variable.
The compiler will consolidate all inline definitions into a single variable definition. This allows us to define variables in a hearder file and have them treated as if there was only one definition in a .cpp file somewhere. These variables also retain their constexpr-ness in all files in which they are included.

```cpp
#ifnedf CONSTANTS_H
#define CONSTANTS_H
namespace constants {
    inline constexpr double pi {3.14159};       // note: now inline constexpr
    inline constexpr double avogadro {6.0221413e23};
    inline constexpr double my_gravity {9.2};   // m/s^2 -- gravity is light on this planet
    // other related constants
}
#endif

---------------------------------------------------------------------------------------------

#include "constants.h"

int main() {
    std::cout << "Enter a radius: ";
    int radius{};
    std::cin >> radius;

    std::cout << "The circumference is: " << 2 * radius * constants::pi;
}
```

***Best practice***
> If you need global constants and your compiler is C++17 capable, prefer defining inline constexpr global variables in a header file.

###Protecting yourself from global destruction
Instead of allowing direct access to the global variable, it's a better practice to "encapsulate" the variable. First, make sure the varialbe can only be accessed from within the file it's decalred in, eg. by making the variable static or const. Second, provide external global "access functions" to work with the varialbe. These functions can ensure proper usage is maintained.
```cpp
namespace constants {
    const double gravity {9.8};         // has internal linkage, is accessible only by this file.
}

double getGravity() {  // this function can be exported to other files to access the global outside of this file
    // We could add logic here if needed later
    // or change the implementation transparently to the callers
    return constants::gravity;
}
```
Third, when writing an otherwise standalone function that uses the global variabe, don't use the variable directly in your function body. Pass it as an argument instead. That way, if your function ever needs to use a different value for some circumstance, you can simply vary the argument. This helps maintain the modularity.
```cpp
#include <iostream>
 
namespace constants {
    constexpr double gravity { 9.8 };
}
 
// This function can calculate the instant velocity for any gravity value (more useful)
double instantVelocity(int time, double gravity) {
    return gravity * time;
}
 
int main() {
    std::cout << instantVelocity(5, constants::gravity); // pass our constant to the function as a parameter
}
```
