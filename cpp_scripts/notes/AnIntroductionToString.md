#An introduction to std::string

When we used operator `>>` to extract a string into variable name, only "John" was extracted, leaving "Doe" inside std::cin, waiting for the next extraction. When we then used operator `>>` to get variable age, it extracted "Doe" instaed of waiting for us to input an age.

### Use std::getline() to input text
The read a full line of input into a string, you're better off using the `std::getline()` function instead. `std::getline()` takes two parameters: the first is `std::cin`, and the second is your string variable.

A good rule of thumb is that after reading a value with std::cin, remove the newline form the stream. This can be done using the following:
```cpp
std::cin.ignore(32767, '\n');       // ignore up to 32767 characters until a \n is removed;
```
If we insert this line directly after reading variable choice, the extraneous newline will be removed from the stream.
>**Rule**
> If reading values with std::cin, it's a good idea to remove the extraneous newline using std::cin.ignore().
### What's that 32767 magic number in your code?
That tells std::cin.ignore() how many characters to ignore up to. We picked that number because it's the largest signed value guaranteed to fit in a (2-byte) integer on all platforms.

### Appending strings
You can use operator `+` to concatenate two strings together (returning a new string), or operator += to append a string to the end of an existing string).
