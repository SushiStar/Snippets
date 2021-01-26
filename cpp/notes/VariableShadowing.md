# Variable shadowing (name hiding)
*Eacch block defines its own scope region. When we have a variable inside a nested block that has the same name as a avriable in an outer block, the nested variable "hides" the outer variable in areas where they are both in scope. The is called **naming hiding** or **shadowing**.* 

### Shadowing of local variables
When inside the nested block, there's no way to directly access the shadowed variable from the outer block.

### Shadowing of global variables
Similar to how variables in a nested block can shadow variables in an outer block, local variables with the
same name as global variable will shadow the global variable wherever the local variable is in scope.
However, because the global variables are part of the global namespace, we can use the scope resolution operator (::) with no prefix to tell the compiler we mean the global variable instead of the local variable.

### Avoid variable shadowing
Shadowing of local variables should generally be avoided, as it can lead to inadvertant errors where the wrong variable is used or modified. Some compilers will issue a warning when a variable is shadowed.
For the same reason that we recommend avoiding shadowing local variables, we recommed avoiding shadowing global variables as well. This is trivially avoidable if all of your global names use a "g\_" prefix.
