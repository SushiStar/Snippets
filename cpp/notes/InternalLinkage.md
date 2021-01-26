# Internal Linkage
**An identifier's linkage determines whether other declarations of that name refer to the same object or not.**

### Global varialbes with internal linkage
Global variables with internal linkage are sometimes called internal variables.
To make a non-constant global variable internal, we use the `static`keyword.

`Const` and `constexpr` global variables have internal linkage by default (and don't need the `static` keyword -- if it is used, it will be ignored).

**For advanced readers:**
> The use of the `static` keyword above is an example of a **storage class specifier**, which sets both the name's linkage and its storage duration (but not its scope). The most commonly used `storage class specifier` values are `static, extern, `and `mutable`.  The term `storage class specifier` is mostly used in technical documentations.

### One definition rule and internal linkage
> An objet or function can't have more than one definition, either within a file or a program.
It's worth noting that internal objects (and functions) that are defined in different files are considered to be independent entities (even if their names and types are identical), so there is no violation of the one-definition rule.

### Functions with internal linkage
Functions default to external linkage, but can be set to internal linkage via the static keyword.
```cpp
// This function is declared as static, and can now be used only within this file
// Attempts to access it from another file via a function forward declaration will fail
static int add(int x, int y) {
    return x + y;
}
```

