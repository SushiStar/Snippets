# Default arguments
A **default argument** is a default value provided for a function parameter. If the user does not supply  an argument for the parameter, the user-supplied argument is used.

```cpp
void printValues(int x, int y=10) {
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}
int main() {
    printValues(1);     // y will use default argument 10
    printValues(3, 4);  // y will use user-supplied argument 4
}
```
### Multiple default arguments

1. All default arguments must be for the rightmost parameters.
2. If more than one default argument exists, the leftmost default argument should be the one most likely to be explicitly set by the user.

### Default arguments can only be declared once
Once decalred, a default argument can not be redeclared. That means for a function with a forward declaration and a function definition, the default argument can be declared in either the forward declaration or the function definition, but not both.
Best practice is to declare the default argument in the forward declaration and not in the function definition, as the forward declaration is more likely to be seen by other files (particularly if it's in a header file).

```cpp
#ifndef FOO_H
#define FOO_H
void printValues(int x, int y=10);
#endif
```
>**Rule**
>If the function has a forward declaration, put the default argument there. Otherwise, put them int the function definition.

### Default arguments and function overloading
Functions with default arguments may be overloaded:

```cpp
void print(std::string string);
void print(char ch=' ');
```
However, it is important to note that optional parameters do not count towards the parameters that make the function unique.
