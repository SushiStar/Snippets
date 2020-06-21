#`std::unique_ptr`
`std::unique_ptr` is the C++11 replacement for `std::auto_ptr`. It should be used to manage any dynamically allocated object that is not shared by multiple objects.
That is, `std::unique_ptr` should completely own the object it manages, not share that ownership with other classes. `std::unique_ptr` lives in the `<memory>` header.
```cpp
#include <iostream>
#include <memory> // for std::unique_ptr
class Resource {
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
	std::unique_ptr<Resource> res1{ new Resource{} }; // Resource created here
	std::unique_ptr<Resource> res2{}; // Start as nullptr

	std::cout << "res1 is " << (static_cast<bool>(res1) ? "not null\n" : "null\n");
	std::cout << "res2 is " << (static_cast<bool>(res2) ? "not null\n" : "null\n");

	// res2 = res1; // Won't compile: copy assignment is disabled
	res2 = std::move(res1); // res2 assumes ownership, res1 is set to null

	std::cout << "Ownership transferred\n";

	std::cout << "res1 is " << (static_cast<bool>(res1) ? "not null\n" : "null\n");
	std::cout << "res2 is " << (static_cast<bool>(res2) ? "not null\n" : "null\n");

	return 0;
} // Resource destroyed here when res2 goes out of scope
```
Because `std::unique_ptr` is designed with move semantics in mind, copy initialization and copy assignment are disabled. If you want to transfer the contents managed by `std::unique_ptr`, you must use move semantics. In the program above, we accomplish this via std::move (which converts res1 into an r-value, which triggers a move assignment instead of a copy assignment).

####Accessing the managed object
`std::unique_ptr` has an overloaded operator\* and operator-> that can be used to return the resource being managed. Operator\* returns a reference to the managed resource, and operator-> returns a pointer.

####`std::unique_ptr` and arrays
Unlike `std::auto_ptr`, `std::unique_ptr` is smart enough to know whether to use scalar delete or array delete, so `std::unique_ptr` is okay to use with both scalar objects and arrays.

####`std::make_unique`
C++14 comes with an additional function named std::make_unique(). This templated function constructs an object of the template type and initializes it with the arguments passed into the function.
```cpp
#include <memory> // for std::unique_ptr and std::make_unique
#include <iostream>
class Fraction {
private:
	int m_numerator{ 0 };
	int m_denominator{ 1 };

public:
	Fraction(int numerator = 0, int denominator = 1) : m_numerator{ numerator }, m_denominator{ denominator } {}

	friend std::ostream& operator<<(std::ostream& out, const Fraction &f1) {
		out << f1.m_numerator << "/" << f1.m_denominator;
		return out;
	}
};

int main() {
	// Create a single dynamically allocated Fraction with numerator 3 and denominator 5
	std::unique_ptr<Fraction> f1{ std::make_unique<Fraction>(3, 5) };
	std::cout << *f1 << '\n';

	// Create a dynamically allocated array of Fractions of length 4
	// We can also use automatic type deduction to good effect here
	auto f2{ std::make_unique<Fraction[]>(4) };
	std::cout << f2[0] << '\n';

	return 0;
}
```
>Rule
use `std::make_unique()` instead of creating `std::unique_ptr` and useing new yourself.

####Returning `std::unique_ptr` from a function
```cpp
std::unique_ptr<Resource> createResource() {
	return std::make_unique<Resource>();
}
int main() {
	std::unique_ptr<Resource> ptr{createResource()};
	// do whatever.
	return 0;
}
```
####Passing `std::unique_ptr` to a function
If you want the function to take ownership of the contents of the pointer, pass the `std::unique_ptr` by value. Note that because copy semantics have been disabled, you’ll need to use std::move to actually pass the variable in.
```cpp
#include <memory> // for std::unique_ptr

class Resource {
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
	friend std::ostream& operator<<(std::ostream& out, const Resource &res) {
		out << "I am a resource\n";
		return out;
	}
};

void takeOwnership(std::unique_ptr<Resource> res) {
     if (res) std::cout << *res << '\n';
} // the Resource is destroyed here

int main() {
    auto ptr{ std::make_unique<Resource>() };

//    takeOwnership(ptr); // This doesn't work, need to use move semantics
    takeOwnership(std::move(ptr)); // ok: use move semantics

    std::cout << "Ending program\n";

    return 0;
}
```
####Misusing `std::unique_ptr`
There are two easy ways to misuse `std::unique_ptr`, both of which are easily avoided. First, don't let multiple classes manage the same resource.
```cpp
Resource *res{ new Resource() };
std::unique_ptr<Resource> res1{ res };
std::unique_ptr<Resource> res2{ res };
```
While this is legal syntactically, the end result will be that both res1 and res2 will try to delete the Resource, which will lead to undefined behavior.

Second, don't manually delete the resource out from underneath the `std::unique_ptr`
```cpp
Resource *res{ new Resource() };
std::unique_ptr<Resource> res1{ res };
delete res;
```
If you do, the `std::unique_ptr` will try to delete an already deleted resource, again leading to undefined behavior.
Note that `std::make_unique`() prevents both of the above cases from happening inadvertently.
