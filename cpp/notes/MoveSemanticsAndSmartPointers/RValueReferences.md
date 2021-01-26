#R-value references
L-values and r-values are actually not properties of values, but rather, properties of expressions.
Every expression in C++ has two properties: a type (which is used for type checking) and a **value category** (which is used for certain kinds of syntax checking).

It's simplest to think of an *l-value* (also called a locator value) as a function or an object (or an expression that evaluates to a function or object). All l-values have assigned memory addresses.
It's simplest to think of an *r-value* as "everything that is not an l-value". This notably  includes literals, temporary values, and anonymous objects. r-values are typically evaluated for their values, have expression scope (they die at the end of the expression they are in), and cannot be assigned to. This non-assignment rule makes sense, because assigning a value applies a side-effect to the object. Since r-values have expression scope, if we were assign a value to an r-value, then the r-value would either go out of scope before we had a chance to use the assigned value in the next expression or we'd have to use a variable with a side effect applied more than once in an expression.

L-value references can only be initizlized with modifiable l-values.
L-value references to const objects can be initizlized with l-values and r-values alike. However, those values can't be modified.

An r-value reference is a reference that is designed to be initizlized with an r-value (only). While an l-value reference is created using a single ampersand, an r-value reference is created a double ampersand.
```cpp
int x{5};
int &lref{x};	// l-value reference initialized with l-value x
int &&rref{5};	// r-value reference initialized with r-value 5
```
R-values cannot be initialized with l-values.
R-value references have two properties that are useful. First, r-value references extend the lifespan of the object they are initizlized with to the lifespan of the r-value reference (l-value references to const objects can do this too). Second, non-const r-value references allow you to modify the r-value.

####R-vlaue references as fucntion parameters
R-value references are more often used as function parameters. This is most useful for function overloads when you want to have different behavior for l-value and r-value arguments.
```cpp
void fun(const int &lref) {	// l-value arguments will select this function
	// do something
}
void fun(int &&rref) {	// r-value arguments will select this function
	// do something
}
```
```cpp
int &&ref{5};
fun(ref);
```
actually calls the l-value version of the function. Although variable ref has type *r-value reference to an integer*, it is actually an l-value itself (as are all named variables).
