# Pure virtual functions, abstract base classes, and interface classes
## Pure virtual (abstract) functions and abstrace base classes
C++ allows you to create a special kind of virtual function called a **pure virtual function** (or abstract function) that has no body at all. A pure virtual function simply acts as a placeholder that is meant to be redefined by derived class.

To create a pure virtual function, rather than define a body for the function, we simply assign the function the value 0.
```cpp
class Base {
public:
	const char* sayHi() {return "Hi";}	// a normal non-virtual function
	virtual const char* getName() {return "base";}	// a normal virtual function
	virtual int getValue() = 0;		// a pure virtual function
	int doSomething() = 0;	// Compile error: can not set non-virtual functions to 0
};
```
Using a pure virtual function has two main consequences: First, any class with one or more pure virtual functions becomes an abstract **base class**, which means it cannot be instantiated. Second, any derived class must define a body for this function, or that derived class will be considered an abstract base class as well.

A pure virtual function is useful when we have a function that we want to put in the base class, but only the derived classes know what it should return. A pure virtual function makes it so the base class can not be instantiated, and the derived classes are forced to define these functions before they can be instantiated.

## Interface classes
An **interface class** is a class that has no member variables, and where *all* of the functions are pure virtual. In other words, that class is purely a definition, and has no actual implementation. Interfaces are useful when you want to define the functionality that derived classes must implement, be leave the details of how the derived class implements that functionality entirely up to the derived class.

Interface classes are often named beginning with an 'I'.

Dont't forget to implement a virtual destructor for your interface classes, so that teh proper derived destructor will be called if a pointer to the interface is deleted.

## Virtual base classes
To share a base class, simply insert the "virtual" keyword in the inheritance list of the derived class. This creates what is called a **virtual base class**, which means there is only one base object. The base obejct is shared between all objects in the inheritance tree and it is only constructed once.

First, virtual base classes are always created before non-virtual base classes, which ensures all bases get created before their derived classes. Third, if a class inherits one or more classes that have virtual parents, the most derived class is responsible for constructing the virtual base class. Fourth, all classes inheriting a virtual base class will have a virtual table, even if they would normally not have one otherwise, and thus be larger by a pointer.
