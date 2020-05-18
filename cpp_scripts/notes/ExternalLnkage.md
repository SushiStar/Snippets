#External Linkage
Internal linkage limits the use of an identifier to a single file.
An identifier with **external linkage** can be seen and used both from the file in which it is defined, and from other code files (via a forward declaration). 

###Functions have external linkage by default

###Global variables with external linkage
Global variables with external linkage are sometimes called **external variables**. To make a global varialbe external (and thus accessible by other files), we can use the `extern` keyword.
```cpp
int g_x {2}; // non-constant globals are external by default

extern const int g_y{3}; // const globals can be defined as extern, making them external
extern constexpr int g_z{3}; // constexpr globals can be defined as extern, making them external.

int main() {
    return 0;
}
```
Non-const global variables are external by default (if used, the extern keyword will be ignored).
To actually use an external global variable that has been defined in another file, you also must place a `forward declaration` for the global variable in any other files wishing to use the variable. For variables, creating a forward declaration is also done via the `extern` keyword (with no initialization value).

Variables forward declarations do need the `extern` keyword to help differentiate variables definitions from variable forward declarations.
```cpp
// non-constant
int g_x;            // variable definition (can have initializer if desired)
extern int g_x;     // forward declaration (no initializer)

// constant
extern const int g_y {1};   // variable definition (const requires initializers)
extern const int g_y;       // forward declaration (no initializer)
```

###File scope vs. global scope
Technically, in C++, *all* global variables have "file scope", and the linkage property controls whether tehy can be used in other files or not.
Forward declaration also has file scope -- it can be used from the point of declaration to the end of the file.

###The initialization order problem of global variables
Initialization of global variables happens as part of program startup, before execution of the `main` function. This proceeds in two phases.
The first phase is called `static initialization`. In the static initialization phase, global variables with constexper initializers (including literals) are initizliaed to those values. Also, global variables without initializers are zero-initialized.
The second phase is called `dynamic initialization`. This phase is more complex and nuanced, but the gist of it is that global variables with non-constexpr initializers are initialized.
Within a single file, global variables are generally initialized in order of definition.
Much more of a problem, the order of initialization across different files is not defined.

```cpp
// External global variable definitions:
int g_x;                       // defines non-initialized external global variable (zero initialized by default)
extern const int g_x{ 1 };     // defines initialized const external global variable
extern constexpr int g_x{ 2 }; // defines initialized constexpr external global variable
 
// Forward declarations
extern int g_y;                // forward declaration for non-constant global variable
extern const int g_y;          // forward declaration for const global variable
extern constexpr int g_y;      // not allowed: constexpr variables can't be forward declared
```

