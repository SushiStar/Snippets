#Virtual functions and polymorphism
A **virtual function** is a special type of function that, when called, resolves to the most-derived version of the function that exists between the base and derived class. This capability is known as **polymorphism**. A derived function is considered a match if it has the same signature (name, parameter types, and whether it is const) and return type as the base version of the function. Such functions are called overrides.

To make a function virtual, simply place the 'virtual' keyword before the function declaration.
```cpp
class Base {
public:
	virtual std::string_view getName() const {return "Base";} 	// note addition of virtual keyword
};

class Derived: public Base {
public:
	virtual sdt::string_view getName() const {return "Derived";}
};
int main() {
	Derived derived;
	Base &rBase{derived};
}
```
Because rBase is a reference to the Base portion of a Derived object, when `rBase.getName()` is evaluated, it would normally resolve to `Base::getName()`. However, `Base::getName()` is virtual, which tells the program to go look and see if there are any more-derived versions of the function available between Base and Derived.

###Use of virtual keyword
If a function is marked as virtual, all matching overrides are also considered virtual, even if they are not explicitly marked as such. However, having the keyword virtual on the derived functions does not hurt, and it serves as a useful reminder that the function is a virtual function rather than a normal one.
###Return types of virtual functions
Under normal circumstances, the return type of a virtual function and its override must match.
###Do not call virtual functions from constructors or destructors
Remember that when a Derived class is created, the Base portion is constructed first. If you were to call a virtual function from the Base constructor, and Derived portion of the class hadn't been created yet, it would be unable to call the Derived version of the function becaues there's no Derived object for the Derived function to work on. In C++ it will call the Base version instead.
###The downside of virtual functions
Resolving a virtual function call takes longer than resolving a regular one. Furthermore, the compiler also to allocate extra pointer for each class object that has one or more virtual functions.
