# Class code and header files
C++ provides a way to separate the "declaration" portion of the class from the "implementation" portion. This is done by defining the class member functions of the class as if they were normal functions, but prefix the class name to the function using the scope resolution operator(::).
## Putting class definitions in a header file
Class definitions can be put in a header file of the same name as the class, and the member functions defined outside of the class are put in a .cpp file of teh same name as the class.

>**Doesn't defining a class in a header file viloate the one-definition rule**

Member functions defined inside the class definition are considered implicitly inline. Inline functions are exempt from the one defiinition per program part of the one-definition rule. This means there is no problem defining trivial member functions (such as access functions) inside the class definition itself.

## What should I define in the header file vs the cpp file, and what inside the class definition vs outside?
- For classes used in only one file that aren't generally reusable, define them directly in the signle .cpp file they're used in.
- For classes used in multiple files, or intended for general reuse, define them in a .h file that has the same name as the class.
- Trivial member functions (trivial constructors or destructors, access functions, etc..) can be defined inside the class.
- Non-trivial member functions should be defined in a .cpp file that has the same name as the class.

## Default parameters
Default parameters for member functions should be declared in the class definition (in the header file), where they can be seen by whomever #includes the header.

## Libraries
Your program needs the declarations from the header files in order for the compiler to validate you're writing programs that are syntatically correct. However, the implementations for the classes that belong to the library are contained in a precompiled file that is linked in at the link stage. 
Outside of some open source software, most 3rd party libraries provide only header files, along with a precompiled library file. There are several reasons for this:

1. It's faster to link a precompiled library than to recompile it every time you need it.
2. A single copy of a precompiled library can be shared by many applications, whereas compiled code gets compiled into every executable that uses it.
3. Intellectual property reasons.
