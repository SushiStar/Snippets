#`std::move`
In C++, `std::move` is a standard library function that serves a single purpose -- to convert its argument into an r-value. We can pass an l-value to `std::move`, and it will return an r-value reference.

We can also use std::move when filling elements of a container, such as std::vector, with l-values.
```cpp
#include <iostream>
#include <string>
#include <utility> // for std::move
#include <vector>

int main() {
	std::vector<std::string> v;
	std::string str = "Knock";

	std::cout << "Copying str\n";
	v.push_back(str); // calls l-value version of push_back, which copies str into the array element

	std::cout << "str: " << str << '\n';
	std::cout << "vector: " << v[0] << '\n';

	std::cout << "\nMoving str\n";

	v.push_back(std::move(str)); // calls r-value version of push_back, which moves str into the array element

	std::cout << "str: " << str << '\n';
	std::cout << "vector:" << v[0] << ' ' << v[1] << '\n';

	return 0;
}
```
In the second case, we passed `push_back()` an r-value (actually an l-value converted via `std::move`), so it used move semantics to add an element to the vector. This is more efficient, as the vector element can steal the string’s value rather than having to copy it. In this case, str is left empty.

At this point, it’s worth reiterating that `std::move()` gives a hint to the compiler that the programmer doesn’t need this object any more (at least, not in its current state). Consequently, you should not use `std::move()` on any persistent object you don’t want to modify, and you should not expect the state of any objects that have had `std::move()` applied to be the same after they are moved!
