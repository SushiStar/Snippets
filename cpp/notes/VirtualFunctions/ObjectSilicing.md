# Object silicing
The assigning of a Derived class object to a Base class object is called object slicing (or slicing for short).

#### Silicing and functions

```cpp
void printName(const Base base) // note: base passed by value, not reference
{
    std::cout << "I am a " << base.getName() << '\n';
}
int main()
{
    Derived d{ 5 };
    printName(d); // oops, didn't realize this was pass by value on the calling end
    return 0;
}
```
When you wrote this program, you may not have noticed that base is a value parameter, not a reference.
Therefore, when called as `printName(d)`, we might have expected `base.getName()` to call virtualized function `getName()` and print "I am a Derived", that is not what happens.
Instead, Derived object d is sliced and only the Base portion is copied into the base parameter. When base.`getName()` executes, even though the `getName()` function is virtualized, there’s no Derived portion of the class for it to resolve to.

Of course, slicing here can all be easily avoided by making the function parameter a reference instead of a pass by value (yet another reason why passing classes by reference instead of value is a good idea).

#### Silicing vectors

```cpp
#include <vector>
int main() {
	std::vector<Base> v{};
	v.push_back(Base{ 5 }); // add a Base object to our vector
	v.push_back(Derived{ 6 }); // add a Derived object to our vector

	// Print out all of the elements in our vector
	for (const auto& element : v)
		std::cout << "I am a " << element.getName() << " with value " << element.getValue() << '\n';
	return 0;
}
```
Similar to the previous examples, because the std::vector was declared to be a vector of type Base, when Derived(6) was added to the vector, it was sliced. The elements of `std::vector` must be assignable, whereas references can’t be reassigned (only initialized).
One way to address this is to make a vector of pointers.

#### The Franken object

```cpp
int main()
{
    Derived d1{ 5 };
    Derived d2{ 6 };
    Base &b{ d2 };

    b = d1; // this line is problematic

    return 0;
}
```
The fourth line is where things go astray. Since b points at d2, and we’re assigning d1 to b, you might think that the result would be that d1 would get copied into d2 -- and it would, if b were a Derived. But b is a Base, and the operator= that C++ provides for classes isn’t virtual by default. Consequently, only the Base portion of d1 is copied into d2.
In most cases, you’ll have just created a Frankenobject -- composed of parts of multiple objects.
