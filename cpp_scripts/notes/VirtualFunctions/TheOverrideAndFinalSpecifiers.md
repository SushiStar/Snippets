#The override and findal specifiers, and covariant return types
###The override specifier
A derived class virtual function is only considered an override if its signature and return types match exactly.

To help address the issue of functions that are meant to be overrides but aren't, C++11 introducted the **override specifier**. The override specifier can be applied to any override function by placing the specifier in the same place const would go. If the function does not override a base class function (or is applied to a non-virtual function), the compiler will flag the function as an error.

```cpp
class A {
public:
	virtual const char* getName1(int x) {return "A";}
	virtual const char* getName2(int x) {return "A";}
	virtual const char* getName3(int x) {return "A";}
};
class B {
public:
	virtual const char* getName1(short int x) override {return "B";}	// compiler error, function is not an override;
	virtual const char* getName2(int x) const override {return "B";}	// compiler error, function is not an override;
	virtual const char* getName3(int x) override {return "B";}	// okay, function is an override of A::getName3(int)
};
```
There is no performance penalty for using the override specifier, and it helps avoid teh inadvertent errors. Consequently, we highly recommend using it for every virtual function override you write to ensure you've actually overridden the function you think you have.
>Rule
>Apply the override specifier to every intended override function you write.

###The final specifier
There may be cases where you don't want someone to be able to override a virtual function or inherit from a class. The final specifier can be used to tell the compiler to enforce this.

In the case where we want to restrict the user from overriding a function, the **final specifier** is used in the same place override specifier is:
```cpp
class A {
public:
	virtual const char* getName() {return "A";}
};
class B : public A {
public:
	virtual const char* getName() override final {return "B";}
}
class C: public B {
public:
	virtual const char* getName() override {return "C";}
};	// compile error: overrides B:getName(), which is final
```
In the case where we want to prevent inheriting from a class, the final specifier is applied after teh class name:
```cpp
Class A {
public:
	virtual const char* getName() {return "A";}
};
class B final: public A {	// note use of final specifier here
public:
	virtual const char* getName() {return "B";}
};
class C : public B {	// compile error: cannot inherit from final class
public:
	virtual const char* getName() override {return "C";}
};
```
In the above example, class B is declared final. Thus, when C tries to inherit from B, the compiler will give compoile error.

###Covariant return types
There is one special case in which a derived class virtual function override can have a different return type than the base class and still be considered a matching override.
If the return type of a virtual function is a pointer or a reference to a class, override functions can return a pointer or a reference to a derived class.
These are called covariant return types.
```cpp
class Base {
public:
	// This version of getThis() returns a pointer to a Base class
	virtual Base* getThis() { std::cout << "called Base::getThis()\n"; return this; }
	void printType() { std::cout << "returned a Base\n"; }
};

class Derived : public Base {
public:
	// Normally override functions have to return objects of the same type as the base function
	// However, because Derived is derived from Base, it's okay to return Derived* instead of Base*
	virtual Derived* getThis() { std::cout << "called Derived::getThis()\n";  return this; }
	void printType() { std::cout << "returned a Derived\n"; }
};

int main() {
	Derived d;
	Base *b = &d;
	d.getThis()->printType(); // calls Derived::getThis(), returns a Derived*, calls Derived::printType
	b->getThis()->printType(); // calls Derived::getThis(), returns a Base*, calls Base::printType
	return 0;
}
```
