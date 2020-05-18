#Typedefs and type aliases
Typedefs allow the programmer to craete an alias for a data type, and use the aliased name instead of the actual type name.
By convention, `typedef` names are declared using a '\_t' suffix. This helps indicate that the identifier represents a type, not a variable or function, and also helps prevent naming collisions with other identifiers.
Note that a `typedef` does not define a new type. Rather it is simply an alias (another name) for an existing type. A `typedef` can be used interchangably anywhere a regular type can be used. `typedef`s and type aliases follow the same scoping rules as variables.

###Type aliases
An improved syntax for `typedef`s has been introduced that mimics the way variables are declared. This syntax is called a **type alias**.
```cpp
typedef double distance_t;      // define distance_t as an alias for type double

using distance_t = double;      // define distance_t as an alias for type double
```
These two functions are equivalent. This type alias syntax is cleaner for more advanced typedefing cases, and should be preferred.

###Using type alias for legibility
###Using type aliases for easier code maintenance
###Using type aliases for platform independent coding
###Using type aliases to make complex types simple
> Favor type aliases over typedefs, and use them liberally to document the meaning of your types.
