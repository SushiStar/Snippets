# Adding new functionality to a derived class
You can inherit the base class functionality and then add new functionality, modify existing functionality, or hide functionality you don't want.
#### Adding new functionality to a derived class
To add new functionality to a derived class, simply declare that functionality in the derived class like normal:

```cpp
class Derived: public Base {
public:
	Derived(int value) : Base(value){}
	int getValue() {return m_value;}
};
```
#### Calling inherited functions and overriding behavior
##### Calling a base class function
When a member function is called with a derived class object, the compiler first looks ot see if that member exists in the derived class. If not, it begins walking up the inheritance chain and checking whether the member has been defined in any of the parent classes. ***It uses the first one it finds***.
##### Redefining behaviors
We can make functions work differently with our derived classes by redefining them in the derived class.
To modify the way a function defined in a base class works in the derived class, simply redefine the function in the derived class.
Note that when you redefine a function in the derived class, teh derived function does not inherit the access specifier of the function with the same name in the base class. It uses whatever access specifier it is defined under in the derived class. Therefore, a function that is defined as private in the base class can be redefined as public in the derived class, or vice-versa.
##### Adding to existing functionality.
Sometimes we don't want to completely replace a base class function, but instead want to add additional functionality to it. It is possible to have our derived function call teh base version of the function of the same name (in order to ruse the code) and then add additional functionality to it.

To have a derived function call a base function of the same name, simply do a normal function call, but prefix the function with teh scope qualifier.
```cpp
class Derived : public Base {
public:
	Derived(int value) : Base(value)
	int GetValue() {return m_value;}
	void identify() {
		Base::identify(); 	// call Base::identify() first
		std::cout << "I am a Derived\n";
	}
};
```

#### Hiding inherited functionality

```cpp
class Derived: public Base
{
public:
    Derived(int value)
        : Base(value)
    {
    }

    // Base::printValue was inherited as protected, so the public has no access
    // But we're changing it to public via a using declaration
    using Base::printValue; // note: no parenthesis here
};
```
First, you can only change the access specifiers of base members the derived class would normally be able to access.Therefore, you can never change the access specifier of a private base member to protected or public, because derived classes do not have access to private members of the base class.
Second, using-declarations are teh preferred way of changing access levels. However, you can also change access levels by using an "access declaration".
##### Hiding functionality
In C++, it is not possible to remove or restrict functionality from a base class other than by modifying the source code. However, in a derived class, it is possible to hide functionality that exists in the base class, so that it can not be accessed through the derived class. This can be done simply by changing the relavant access specifier.

```cpp
#include <iostream>
class Base
{
public:
	int m_value;
};

class Derived : public Base
{
private:
	using Base::m_value;

public:
	Derived(int value)
	// We can't initialize m_value, since it's a Base member (Base must initialize it)
	{
		// But we can assign it a value
		m_value = value;
	}
};
```
You can also mark member functions as deleted in the derived class, which ensures they can't be called at all through a derived object:
```cpp
class Base
{
private:
	int m_value;

public:
	Base(int value)
		: m_value(value)
	{
	}

	int getValue() { return m_value; }
};

class Derived : public Base
{
public:
	Derived(int value)
		: Base(value)
	{
	}
	int getValue() = delete; // mark this function as inaccessible
};
```
