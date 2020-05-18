#Static local variables
Local variable have `automatic duration` by default, which means they are created at the point of definition, and destroyed when the block is exited.
Using the `static` keyword on a local variable changes its duration from `automatic duration` to `static duration`. This means the varialbe is now created at the start of the program, and destroyed at the end of the program (just like a global variable).
Just like we use "g\_" to prefix global variables, it's common to use "s\_" to prefix static (static duration) local variables.
One of the most common use for static duration local variables is for unique ID generators.

Static variables offer some of the benefit of global variables (they don't get destoryed until the end of the program) while limiting their visibility to block scope. This makes them safe for use even if you change their values regularly.
***Best Practice***
> Avoid `static` local variables, unless the variable never needs to be reset. `static` local variables decrease reusability and make functions hard to reason about.

## Linkage summary
An identifier's *linage* determines whether multiple declarations of an identifier refer to the same identifier or not.
* An identifier with no linkage means the identifier only refers to itself. This includes:
    * Local variables
    * User-defined type definitions (such as enums and classes) declared inside a block
* An identifier with internal linkage can be accessed anywhere within the file it is declared. This inlcudes:
    * Static global variables (initialized or uninitialized)
    * Static functions
    * Const global variables
    * Functions declared inside an unnamed namespace
    * User-defined type definitions (such as enums and classes) declared inside an unnmaed namespace
* An identifier with external linkage can be accessed anywhere within the file it is declared, or other files (via a forward declaration). This includes:O
    * Functions
    * Non-const global variables (initialized or uninitialized)
    * Extern const global variables
    * Inline const global variables
    * User-defined type definitions (such as enums and classes) declared inside a namespace or in the global scope.

Identifiers with external linkage will generally cause a duplicate definition linker error if the definitions are compiled into more than one .cpp file (due to  violating the one-definition rule).
