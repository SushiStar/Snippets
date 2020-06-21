#Circular dependency issues with `std::shared_ptr`, and `std::weak_ptr`
```cpp
#include <iostream>
#include <memory> // for std::shared_ptr
#include <string>

class Person {
	std::string m_name;
	std::shared_ptr<Person> m_partner; // initially created empty

public:
	Person(const std::string &name): m_name(name) {
		std::cout << m_name << " created\n";
	}
	~Person() {
		std::cout << m_name << " destroyed\n";
	}

	friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2) {
		if (!p1 || !p2)
			return false;

		p1->m_partner = p2;
		p2->m_partner = p1;

		std::cout << p1->m_name << " is now partnered with " << p2->m_name << "\n";
		return true;
	}
};

int main() {
	auto lucy = std::make_shared<Person>("Lucy"); // create a Person named "Lucy"
	auto ricky = std::make_shared<Person>("Ricky"); // create a Person named "Ricky"

	partnerUp(lucy, ricky); // Make "Lucy" point to "Ricky" and vice-versa

	return 0;
}
```
At the end of the function, the ricky shared pointer goes out of scope first. When that happens, ricky checks if there are any other shared pointers that co-own the Person “Ricky”. There are (Lucy’s m\_partner). Because of this, it doesn’t deallocate “Ricky” (if it did, then Lucy’s m\_partner would end up as a dangling pointer). At this point, we now have one shared pointer to “Ricky” (Lucy’s m\_partner) and two shared pointers to “Lucy” (lucy, and Ricky’s m\_partner).

Next the lucy shared pointer goes out of scope, and the same thing happens. The shared pointer lucy checks if there are any other shared pointers co-owning the Person “Lucy”. There are (Ricky’s m\_partner), so “Lucy” isn’t deallocated. At this point, there is one shared pointer to “Lucy” (Ricky’s m\_partner) and one shared pointer to “Ricky” (Lucy’s m\_partner).

Then the program ends -- and neither Person “Lucy” or “Ricky” have been deallocated! Essentially, “Lucy” ends up keeping “Ricky” from being destroyed, and “Ricky” ends up keeping “Lucy” from being destroyed.

It turns out that this can happen any time shared pointers form a circular reference.

####Circular references
A Circular reference (also called a **cyclical reference** or a **cycle**) is a series of references where each object references the next, and the last object references back to the first, causing a referential loop.

##`std::weak_ptr`
A `std::weak_ptr` is an observer -- it can observe and access the same object as a `std::shared_ptr` (or other `std::weak_ptrs`) but it is not considered an owner. Remember, when a std::shared pointer goes out of scope, it only considers whether other `std::shared_ptr` are co-owning the object. `std::weak_ptr` does not count!
```cpp
#include <iostream>
#include <memory> // for std::shared_ptr and std::weak_ptr
#include <string>

class Person {
	std::string m_name;
	std::weak_ptr<Person> m_partner; // note: This is now a std::weak_ptr

public:
	Person(const std::string &name): m_name(name) {
		std::cout << m_name << " created\n";
	}
	~Person() {
		std::cout << m_name << " destroyed\n";
	}

	friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2) {
		if (!p1 || !p2)
			return false;
		p1->m_partner = p2;
		p2->m_partner = p1;
		std::cout << p1->m_name << " is now partnered with " << p2->m_name << "\n";
		return true;
	}
};

int main() {
	auto lucy = std::make_shared<Person>("Lucy");
	auto ricky = std::make_shared<Person>("Ricky");

	partnerUp(lucy, ricky);

	return 0;
}
```
####Using `std::weak_ptr`
The downside of `std::weak_ptr` is that `std::weak_ptr` are not directly usable (they have no operator->). To use a `std::weak_ptr`, you must first convert it into a `std::shared_ptr`. Then you can use the `std::shared_ptr`. To convert a `std::weak_ptr` into a `std::shared_ptr`, you can use the `lock()` member function. Here’s the above example, updated to show this off:
```cpp
#include <iostream>
#include <memory> // for std::shared_ptr and std::weak_ptr
#include <string>

class Person {
	std::string m_name;
	std::weak_ptr<Person> m_partner; // note: This is now a std::weak_ptr

public:

	Person(const std::string &name) : m_name(name) {
		std::cout << m_name << " created\n";
	}
	~Person() {
		std::cout << m_name << " destroyed\n";
	}

	friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2) {
		if (!p1 || !p2)
			return false;

		p1->m_partner = p2;
		p2->m_partner = p1;

		std::cout << p1->m_name << " is now partnered with " << p2->m_name << "\n";

		return true;
	}

	const std::shared_ptr<Person> getPartner() const { return m_partner.lock(); } // use lock() to convert weak_ptr to shared_ptr
	const std::string& getName() const { return m_name; }
};

int main() {
	auto lucy = std::make_shared<Person>("Lucy");
	auto ricky = std::make_shared<Person>("Ricky");

	partnerUp(lucy, ricky);

	auto partner = ricky->getPartner(); // get shared_ptr to Ricky's partner
	std::cout << ricky->getName() << "'s partner is: " << partner->getName() << '\n';

	return 0;
}
```
