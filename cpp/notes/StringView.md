#An introduction to std::stering_view
Unlike `std::string`, which keeps its own copy of the string, `std::string_view` provides a *view* of a string that is defined elsewhere.
```cpp
#include <iostream>
#include <string_view>
int main() {
    std::string_view text{"hello"};     // view the text "hello", which is stored in the binary
    std::string_view str{text};         // view of the same "hello"
    std::string_view more{str};         // view of the same "hello"
    return 0;
}
```
When we copy a `std::string_view`, the new `std::string_view` observes the same string as the copied-from `std::string_view` is observing. `std::string_view` is not only fast, but has many of the functions that we know from `std::string`.
Because `std::string_view` doesn't create a copy of the string, if we change the viewed string, the changes are reflected in the `std::string_view`.
>**Best practice**
>Use `std::string_view` instead of C-style strings.
>Prefer `std::string_view` over `std::string` for read-only strings, unless you already have a `std::string`.

###View modification functions
`std::string_view` contains functions that let us manipulate the *view* of the string. This allows us to change the view without modifying the viewed string.
A `std::string_view` cannot be opened back up. Once you change the visible area, you can't go back.

###Ownership issues
Being only a view, a `std::string_view`'s life time is independent of that of the string it is viewing. If the viewed string goes out of scope, `std::string_view` has nothing to obserview and accessing it causes undefined behavior.
The same can happen when we create a `std::string_view` from a `std::string` and modify the `std::string`. Modifying a `std::string` can cause its internal string to die and be replaced bwith a new one in a different place. The `std::string_view` will still look at where the old string was, but it's not there anymore.

>**Warning**
>Make sure that the underlying string viewed with a `std::string_view` does not go out of scope and isn't modified while using the `std::string_view`.

###Converting a `std::string_view` to a `std::string`
And `std::string_view` will not implicitly convert to a `std::string`, but can be explicitly converted:
```cpp
#include <iostream>
#include <string>
#include <string_view>
 
void print(std::string s)
{
  std::cout << s << '\n';
}
 
int main()
{
  std::string_view sv{ "balloon" };
 
  sv.remove_suffix(3);
 
  // print(sv); // compile error: won't implicitly convert
 
  std::string str{ sv }; // explicit conversion
 
  print(str); // okay
 
  print(static_cast<std::string>(sv)); // okay
	   
  return 0;
}
```
###Converting a `std::string_view` to a C-style string
Some old functions (such as the old strlen function) still expect C-style strings. To convert a `std::string_view` to a C-style string, we can do so by first converting to a `std::string`.
###Opening the window via the data() function
The string being viewed by a `std::string_view` can be accessed by using the `data()` function, which returns a C-style string. This provides fast access to the string being viewed. But it should also only be used if the `std::string`'s view hasn't been modified.
