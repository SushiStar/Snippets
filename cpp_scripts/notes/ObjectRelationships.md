#Object relationships
Programming is full of recurring patterns, relationships and hierarchies. Particularly when it comes to programming objecst, the same pattern that govern real-life objects are applicable to the programming objects  we create ourselves. By examining these in more detail, we can better understand how to improve code resusability and write classes that are more extensible.

##Relationships between objects
There are many different kinds of relationships two objects have in real-life, and we use specific "relation type" words to describe these relationships: "part-of", "has-a", "uses-a", "depends-on", and "member-of", and show how they can be useful in the context of C++ classes.

##Composition
The process of building complex cbjects from simpler ones is called **object-composition**.
Broadly speaking, object composition models a "has-a" relationship between two objects. The complex object is sometimes called the whole, or the parent. The simpler object is often called the part, child, or component.
###Type of object composition
There are two baisc subtypes of object composition: composition and aggregation.
The term "composition" is often used to refer to both composition and aggregation, not just to composition subtype.
####Composition
To qualify as a composition, an object and  a part must have the following relationship:
- The part (member) is part of the object (class)
- The part (member) can only belong to one object (class) at a time
- The part (member) has its existence managed by the object (class)
- Teh part (member) does not know about the the existence of the object (class)

In a composition relationship, the object is responsible for the existence of the parts. Most often, this means the part is created when the object is created, and destroyed when teh object is destroyed. But more broadly, it means the object manages ths part's lifetime in such a way that the user of the object does not need to get involved.
And finally, the part doesn't know about the existence of teh whole.
We call this **unidirectional** relationship.

####Implementing compositions
Compositions are one of the easiest relationship types to implement in C++. They are typically created as structs or classes with normal data members. because these data members exist directly as part of the struct/class their lifetime are bound to that of the class instance itself.

Composition that need to do dynamic allocation or deallocation may be implemented using pointer data members. In this case, the composition class should be responsible for doing all necessary memory management itself (not the user of the class).

####Variants on the composition theme
- A composition may defer creation of some parts until they are needed.
- A composition may opt to use a part that has been given to it as input rather than create the part itself.
- A composition may delegate destruction of its parts to some other object (e.g. to a garbage collection routine).
The key point is that the composition should manage its parts without the user of the composition needing to manage anything.

####Composition and subclasses
A good rule of thumb is that each class should be built to accomplish a single task. That task should be either be storage and manipulation of some kind of data or the coordination of subclasses.

##Aggregation
To qualify as an aggregation, a whole object and its parts must have the following relationship:
- The part (member) is part of the object (class)
- The part (member) can belong to more than one object (class) at a time.
- The part (member) does *not* have its existence managed by the object (class)
- The part (member) does not know about the existence of the object (class)
When an aggregation is created, the aggregation is not responsible for creating the parts. When an aggregation is destroyed, the aggregation is not responsible for destroying the parts.

####Implementing aggregations
Because aggregations are similar to compositions in that they are both part-whole relationships, they are implemented almost identically, and the difference between them is mostly semantic. In a composition, we typically add our parts to the composition using normal member variables (or pointers where the allocation and deallocation process is handled by the composition class).

In an aggregation, we also add parts as member variables. However, these member variables are typically either references or pointers that are used to point at objects that have been created outside of the class. Consequently, an aggregation usually either takes the objects it is going to point to as constructor parameters, or it begins empty and the subobjects are added later via access functions or operators.
```cpp
#include <iostream>
#include <string>
class Teacher {
private:
	std::string n_name{};
public:
	Teacher(const std::string &name) {}
	const std::string &getName() const {return m_name;}
};

class Department {
private:
	const Teacher &m_teacher; 	// this dept holds only one teacher for simplicity
public:
	Department(const Teacher &teacher) : m_teacher{teacher}{}
};

int main() {
	// create a teacher outside the scope of the Department
	Teacher bob{"Bob"}; 	// create a teacher
	{
		// create a department and use the constructor parameter to pass
		// teh teacher to it
		Department department{bob};
	}	// department goes out of scope here and is destroyed
	// bob still exists here, but the department doesn't
	std::cout << bob.getName() << " still exixts!\n";
	return 0;
}
```
>Rule
>Implement the simplest relationship type that meets the needs of your program, not what seems right in real-life.

While aggregations can be extremely useful, they are also potentially more dangerous, because aggregations do not handle deallocation of their parts. Deallocations are left to an external party to do. If the external party no longer has a pointer or reference to the abandoned parts, or if it simply forgets to do the cleanup (assuming the class will handle that), then the memory will be leaked.

####`std::reference_wrapper`
In the `Department/Teacher` example above, we used a reference in the `Department` to store the `Teacher`. This works fine if there is only one `Teacher`, but if there is a list of `Teacher`, say `std::vector`, we can't use references anymore.
```cpp
std::vector<const Teacher&> m_teachers{}; 	// Illegal
```
Essentially, `std::reference_wrapper` is a class that acts like a reference, but also allows assignment and copying, so it's compatible with lists like `std::vector`.
The good news is that you don't really need to understand how it works to use it. All you need to know are three things:
1. `std::reference_wrapper` lives in the `<functional>` header.
2. When you create your `std::reference_wrapper` wrapped object, the object can't be an anonymous object (since anonymous objects have expression scope would leave the reference dangling).
3. When you want to get your object back out of `std::reference_wrapper`, you use the `get()` member function.
```cpp
#include <functional>
#include <iostream>
#include <vector>
#include <string>

int main() {
	std::string tom{"Tom"};
	std::string berta{"Berta"};
	std::vector<std::reference_wrapper<std::string>> names{tom, berta};
	std::string jim{"Jim"};
	names.push_back(jim);

	for (auto name : names) {
		// use the get() member function to get the referenced string.
		name.get() += " Beam";
	}
	std::cout << jim << '\n'; // Jim Beam
	return 0;
}
```
To create a vector of const references, we'd have to add const before the `std::string` like so
```cpp
// Vector of const references to std::string
std::vector<std::reference_wrapper<const std::string>> names{tom, berta};
```
