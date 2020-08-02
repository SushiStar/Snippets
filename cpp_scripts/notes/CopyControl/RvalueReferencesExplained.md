# C++ Rvalue References Explained
Rvalue references are a feature of C++ that was added with the C++11 standard. Rvalue references solve at least two problems:
  1. Implementing move semantics
  2. Perfect forwarding

The original definition of lvalues and rvalues from the earliest days of C is as follows: An lvalue is an expression e that may appear on the left or on the right hand side of an assignment, whereas an rvalue is an expression that can only appear on the right hand side of an assignment.
```cpp
int a = 42;
int b = 43;

// a and b are both l-values:
a = b;        // ok
b = a;        // ok
a = a * b;    // ok

// a * b is an r-value:
int c = a * b;    // ok, r-value on the right hand side of the assignment
a * b = 42;       // error, r-value on left hand side of the assignment
```

**An lvalue is an expression that refers to a memory location and allows us to take the address of that memory location via the & operator. An rvalue is an expression that is not an lvalue.**
```cpp
// lvalues:
int i = 42;
i = 43;                 // ok, i is an lvalue
int* p = &i;            // ok, i is an lvalue
int& foo();
foo() = 42;             // ok, foo() is an lvalue
int* p1 = &foo();       // ok, foo() is an lvalue

// rvalues:
int foobar();
int j = 0;
j = foobar();           // ok, foobar() is an rvalue
int* p2 = &foobar();    // error, cannot take the address of an rvalue
j = 42;                 // ok, 42 is an rvalue
```

### Rvalue References
If X is any type, then X&& is called an rvalue reference to X. For better distinction, the ordinary reference X& is now also called an lvalue reference.
An rvalue reference is a type that behaves much like the ordinary reference X&, with several exceptions. The most important one is that when it comes to function overload resolution, lvalues prefer old-style lvalue references, whereas rvalues prefer the new rvalue references:
```cpp
void foo(X& x);         // lvalue reference overload
void foo(X&& x);        // rvalue reference overload

X x;
X foobar();

foo(x);               // argument is lvalue: calls foo(X&)
foo(foobar());        // argument is rvalue: calls foo(X&&)
```
So the gist of it is:
> Rvalue references allow a function to branch at compile time (via overload resolution) on the condition "Am I being called on an lvalue or an rvalue?"

It is true that you can overload any function in this manner, as shown above. But in the overwhelming majority of cases, this kind of overload should occur only for copy constructors and assignment operators, for the purpose of achieving move semantics:
```cpp
X& X::operator=(X const & rhs);   // classical implementation

X& X::operator=(X&& rhs) {
  // Move semantics: exchange content between this and rhs
  return *this;
}
```

### Forcing Move Semantics
Consider the following example:
```cpp
template<class T>
void swap(T& a, T& b) {
  T tmp(a);
  a = b;
  b = tmp;
}

X a, b;
swap(a, b);
```
In C++11, there is an std library function called std::move that comes to our rescue. It is a function that turns its argument into an rvalue without doing anything else. Therefore, in C++11, the std library function swap looks like this:
```cpp
template<class T>
void swap(T& a, T& b) {
  T tmp(std::move(a));
  a = std::move(b);
  b = std::move(tmp);
}

X a, b;
swap(a, b);
```
Using `std::move` wherever we can, as shown in the swap function above, gives us the following important benefits:
* For those types that implement move semantics, many standard algorithms and operations will use move semantics and thus experience a potentially significant performance gain. An important example is inplace sorting: inplace sorting algorithms do hardly anything else but swap elements, and this swapping will now take advantage of move semantics for all types that provide it.
* The STL often requires copyability of certain types, e.g., types that can be used as container elements. Upon close inspection, it turns out that in many cases, moveability is enough. Therefore, we can now use types that are moveable but not copyable (unique_pointer comes to mind) in many places where previously, they were not allowed. For example, these types can now be used as STL container elements.

Consider a simple assignment between variables, like this:
```cpp
a = b;
```
What do you expect to happen here? You expect the object held by `a` to be replaced by a copy of `b`, and in the course of this replacement, you expect the object formerly held by `a` to be destructed. Now consider the line
```cpp
a = std::move(b);
```
If move semantics are implemented as a simple swap, then the effect of this is that the objects held by a and b are being exchanged between a and b. Nothing is being destructed yet. The object formerly held by a will of course be destructed eventually, namely, when b goes out of scope. Unless, of course, b becomes the target of a move, in which case the object formerly held by a gets passed on again. Therefore, as far as the implementer of the copy assignment operator is concerned, it is not known when the object formerly held by a will be destructed.

So in a sense, we have drifted into the netherworld of non-deterministic destruction here: a variable has been assigned to, but the object formerly held by that variable is still out there somewhere. That's fine as long as the destruction of that object does not have any side effects that are visible to the outside world. But sometimes destructors do have such side effects. An example would be the release of a lock inside a destructor. Therefore, any part of an object's destruction that has side effects should be performed explicitly in the rvalue reference overload of the copy assignment operator:
```cpp
X& X::operator=(X&& rhs) {
  // Perform a cleanup that takes care of at least those parts of the
  // destructor that have side effects. Be sure to leave the object
  // in a destructible and assignable state.

  // Move semantics: exchange content between this and rhs

  return *this;
}
```

### Is an Rvalue Reference an Rvalue?
> Things that are declared as rvalue reference can be lvalues or rvalues. The distinguishing criterion is: if it has a name, then it is an lvalue. Otherwise, it is an rvalue.
In the example above, the thing that is declared as an rvalue reference has a name, and therefore, it is an lvalue:
```cpp
void foo(X&& x) {
  X anotherX = x; // calls X(X const & rhs)
}
```
Here is an example of something that is declared as an rvalue reference and does not have a name, and is therefore an rvalue:
```cpp
X&& goo();
X x = goo(); // calls X(X&& rhs) because the thing on the right hand side has no name
```
And here's the rationale behind the design: Allowing move sematics to be applied tacitly to something that has a name, as in
```cpp
X anotherX = x; // x is still in scope!
```
would be dangerously confusing and error-prone because the thing from which we just moved, that is, the thing that we just pilfered, is still accessible on subsequent lines of code. But the whole point of move semantics was to apply it only where it "doesn't matter," in the sense that the thing from which we move dies and goes away right after the moving. Hence the rule, "If it has a name, then it's an lvalue."

Suppose you have written a class Base, and you have implemented move semantics by overloading Base's copy constructor and assignment operator:
```cpp
Base(Base const & rhs); // non-move semantics
Base(Base&& rhs);       // move semantics
```
Now you write a class Derived that is derived from Base. **In order to assure that move semantics is applied to the Base part of your Derived objects, you must overload Derived's copy constructor and assignment operator as well.** Let's look at the copy constructor. The copy assignment operator is handled analogously. The version for lvalues is straightforward:
```cpp
Derived(Derived const & rhs)
  : Base(rhs)
{
  // Derived-specific stuff
}
```
The version for rvalues has a big fat subtlety:
```cppp
Derived(Derived&& rhs) : Base(rhs) // wrong: rhs is an lvalue
{
  // Derived-specific stuff
}
Derived(Derived&& rhs)
  : Base(std::move(rhs)) // good, calls Base(Base&& rhs)
{
  // Derived-specific stuff
}
```

### Move Semantics and Compiler Optimizations
Consider the following function definition:
```cpp
X foo() {
  X x;
  // perhaps do something to x
  return x;
}
```
Now suppose that as before, X is a class for which we have overloaded the copy constructor and copy assignment operator to implement move semantics. If you take the function definition above at face value, you may be tempted to say, wait a minute, there is a value copy happening here from x to the location of foo's return value. Let me make sure we're using move semantics instead:
```cpp
X foo()
{
  X x;
  // perhaps do something to x
  return std::move(x); // making it worse!
}
```
Unfortunately, that would make things worse rather than better. Any modern compiler will apply return value optimization to the original function definition. In other words, rather than constructing an X locally and then copying it out, the compiler would construct the X object directly at the location of foo's return value. Rather obviously, that's even better than move semantics.

### Perfect Forwarding: The Problem
Consider the following simple factory function:
```cpp
template<typename T, typename Arg>
shared_ptr<T> factory(Arg arg)
{
  return shared_ptr<T>(new T(arg));
}
```
Obviously, the intent here is to forward the argument arg from the factory function to T's constructor. Ideally, as far as arg is concerned, everything should behave just as if the factory function weren't there and the constructor were called directly in the client code: perfect forwarding. The code above fails miserably at that: it introduces an extra call by value, which is particularly bad if the constructor takes its argument by reference.

The most common solution, chosen e.g. by boost::bind, is to let the outer function take the argument by reference:
```cpp
template<typename T, typename Arg>
shared_ptr<T> factory(Arg& arg)
{
  return shared_ptr<T>(new T(arg));
}
```
That's better, but not perfect. The problem is that now, the factory function cannot be called on rvalues:
```cpp
factory<X>(hoo());  // error if hoo returns by value
factory<X>(41);     // error
```
This can be fixed by providing an overload which takes its argument by const reference:
```cpp
template<typename T, typename Arg>
shared_ptr<T> factory(Arg const & arg)
{
  return shared_ptr<T>(new T(arg));
}
```
There are two problems with this approach. Firstly, if factory had not one, but several arguments, you would have to provide overloads for all combinations of non-const and const reference for the various arguments. Thus, the solution scales extremely poorly to functions with several arguments.
Secondly, this kind of forwarding is less than perfect because it blocks out move semantics: the argument of the constructor of T in the body of factory is an lvalue. Therefore, move semantics can never happen even if it would without the wrapping function.

### Perfect Forwarding: The Solution
C++11, by contrast, introduces the following reference collapsing rules1:
```cpp
A& & becomes A&
A& && becomes A&
A&& & becomes A&
A&& && becomes A&&
```
Secondly, there is a special template argument deduction rule for function templates that take an argument by rvalue reference to a template argument:
```cpp
template<typename T>
void foo(T&&);
```

Here the following apply:
1. When foo is called on an lvalue of type A, then T resolves to A& and hence, by the reference collapsing rules above, the argument type effectively becomes A&.
2. When foo is called on an rvalue of type A, then T resolves to A, and hence the argument type becomes A&&.
