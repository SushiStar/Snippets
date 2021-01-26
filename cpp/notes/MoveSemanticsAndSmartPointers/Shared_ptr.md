#`std::shared_ptr`
Unlike `std::unique_ptr`, which is designed to singly own and manage a resource, `std::shared_ptr` is meant to solve the case where you need multiple smart pointers co-owning a resource.
```cpp
#include <iostream>
#include <memory> // for std::shared_ptr

class Resource {
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};

int main() {
	// allocate a Resource object and have it owned by std::shared_ptr
	Resource *res = new Resource;
	std::shared_ptr<Resource> ptr1(res);
	{
		std::shared_ptr<Resource> ptr2(ptr1); // use copy initialization to make another std::shared_ptr pointing to the same thing

		std::cout << "Killing one shared pointer\n";
	} // ptr2 goes out of scope here, but nothing happens

	std::cout << "Killing another shared pointer\n";
	return 0;
} // ptr1 goes out of scope here, and the allocated Resource is destroyed
```
####`std::make_shared`
```cpp
#include <iostream>
#include <memory> // for std::shared_ptr

class Resource {
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};

int main() {
	// allocate a Resource object and have it owned by std::shared_ptr
	auto ptr1 = std::make_shared<Resource>();
	{
		auto ptr2 = ptr1; // create ptr2 using copy initialization of ptr1

		std::cout << "Killing one shared pointer\n";
	} // ptr2 goes out of scope here, but nothing happens

	std::cout << "Killing another shared pointer\n";
	return 0;
} // ptr1 goes out of scope here, and the allocated Resource is destroyed
```
####Shared pointers can be created from unique pointers
A std`::unique_ptr can` be converted into a `std::shared_ptr` via a special `std::shared_ptr` constructor that accepts a `std::unique_ptr` r-value. The contents of the `std::unique_ptr` will be moved to the `std::shared_ptr`.

However, `std::shared_ptr` can not be safely converted to a `std::unique_ptr`. This means that if you’re creating a function that is going to return a smart pointer, you’re better off returning a `std::unique_ptr` and assigning it to a `std::shared_ptr` if and when that’s appropriate.
