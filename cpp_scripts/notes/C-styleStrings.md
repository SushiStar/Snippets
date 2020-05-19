#C-style strings
A **C-style string** is simply an array of characters that uses a null terminator. A **null terminator** is a special character ('\0', ascii code 0) used to indicate the end of the string. More generically, a C-style string is called a **null-terminated string**.
To define a C-style string, simply declare a char array and initizlize it with a string literal:
```cpp
char myString[]{"string"};  // although "string" only has 6 characters, C++ automatically adds a null terminator to the end o fthe string for us.
```
###C-style strings and std::cin
```cpp
#include <iostream>
#include <iterator> // for std::size
 
int main()
{
    char name[255]; // declare array large enough to hold 255 characters
    std::cout << "Enter your name: ";
    std::cin.getline(name, std::size(name));
    std::cout << "You entered: " << name << '\n';
 
    return 0;
}
```
Use getline() to guarantee that no more than `std::size(name)` characters are read from `std::cin`.
###Manipulating C-style strings
C++ provides many functions to manipulate C-style strings as part of the `<cstring>` library.
`strcyp()` allows you to copy a string to another string. More commonly, this is used to assign a value to a string:
```cpp
#include <cstring>
int main() {
    char source[]{"Copy this!"};
    char dest[50];
    std::strcpy(dest, source);
    std::cout << dest << '\n';
    return 0;
}
```
However, strcpy() can easily cause array overflows if you're not careful.
Many programmers recommend using `strncpy()` instead, which allows you to specify the size of the buffer, and ensures overflow doesn't occur. Unfortunately, strncpy() doesn't ensure strings are null terminated, which still leaves plenty of room for array overflow.
In C++11, `strcpy_s()` is preferred, which adds a new parameter to define the size of the destination. However, not all compilers support this function, and to use it, you have to define `__STDC__WANT_LIB_EXT1__` with integer value 1.
```cpp
#define __STDC_WANT_LIB_EXT1__ 1
#include <cstring> // for strcpy_s
int main()
{
    char source[]{ "Copy this!" };
    char dest[5]; // note that the length of dest is only 5 chars!
    strcpy_s(dest, 5, source); // A runtime error will occur in debug mode
    std::cout << dest << '\n';
 
    return 0;
}
```
Another useful function is the strlen() function, which returns the length of the C-style string (without the null terminator).
```cpp
#include <iostream>
#include <cstring>
#include <iterator> // for std::size
 
int main()
{
    char name[20]{ "Alex" }; // only use 5 characters (4 letters + null terminator)
    std::cout << "My name is: " << name << '\n';
    std::cout << name << " has " << std::strlen(name) << " letters.\n";
    std::cout << name << " has " << std::size(name) << " characters in the array.\n"; // use sizeof(name) / sizeof(name[0]) if not C++17 capable
 
    return 0;
}
```
### Don't use C-style strings
>Rule
>use `std::string` or `std::string_view` instead of C-style strings.
