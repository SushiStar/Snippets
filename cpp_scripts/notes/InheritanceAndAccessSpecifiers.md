#Inheritance and access specifiers
###The protected access specifier
The **protected** access specifier allows the class the member belongs to, friends, and derived classes to access the member. However, protected members are not accessible from outside the class.
```cpp
class Base {
public:
	int m_public; 	// can be accessed by anybodhy
protected:
	int m_protected;	// can be accessed by Base members, friends, and derived classes
private:
	int m_private; 	// can only be accessed by Base members and friends (but not derived classes)
};

class Deriveds : public Base {
public:
	Derived() {
		m_public = 1; 	// allowed
		m_protected = 2; // allowed
		m_private = 3; // not allowed
	}
};
```
With a protected attribute in a base class, derived classes can access that member directly. This means that if you later change anything about that protected attribute, you'll probably need to change both the base class AND all of the derived classes.

In a nutshell, when members are inherited, the access specifier for an inherited member may be changed (in the derived class only) depending on the type of inheritance used. Put another way, members that were public or protected in the base class may change access specifiers in the derived class.

- A class can always access its own (non-inherited) members
- The public accesses the members of a class based on the access specifiers of the class it is accessing.
- A class accesses inherited members based on the access specifier inherited from the parent class. This varies depending on the access specifier and type of inheritance used.

###Public inheritance
When you inherit a base class publicly, inherited public members stay public, and inherited protected members stay protected. Inherited private members, which were inaccessible because they were private in the base class, stay inaccessible.
>Rule
>Use public inheritance unless you have a specific reason to do otherwise.
###Protected inheritance
Protected inheritance is the least common method inheritance. It is almost never used, except in very particular cases. With protected inheritance, the public and protected members become protected, and private members stay inaccessible.
###Private inheritance
With private inheritance, all members from the base class are inherited as private. This means private members stay private, and protected and public members become private.
Note that this does not affect the way that the derived class accesses members inherited from its parent! It only affects the code trying to access those members through the derived class.
```cpp
class Base
{
public:
    int m_public;
protected:
    int m_protected;
private:
    int m_private;
};

class Pri: private Base // note: private inheritance
{
    // Private inheritance means:
    // Public inherited members become private (so m_public is treated as private)
    // Protected inherited members become private (so m_protected is treated as private)
    // Private inherited members stay inaccessible (so m_private is inaccessible)
public:
    Pri()
    {
        m_public = 1; // okay: m_public is now private in Pri
        m_protected = 2; // okay: m_protected is now private in Pri
        m_private = 3; // not okay: derived classes can't access private members in the base class
    }
};
```
Private inheritance can be useful when the derived class has no obvious relationship to the base class, but uses the base class for implementation internally. In such a case, we probably don't want the public interface of the base class to be exposed through objects of the derived class (as it would be if we inherited publicly).
