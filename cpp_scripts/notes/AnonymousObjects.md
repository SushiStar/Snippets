# Anonymous Objects
An **anonymous object** is essentially a value that has no name. Because they have no name, there's no way to refer to them beyond the point they are created. Consequently, they have "expression scope", meaning they are created, evaluated, and destroyed all within a single expression:

```cpp
int add(int x, int y) {
	return x+y;	// an anonymous object is created to hold and return the result of x+y
}
```
### Anonymous class objects
It is possible to construct anonymous objects for our own classes types as well. This is done by creating objects like normal, but omitting the variable name.

```cpp
Cents cents(5); // normal variable
Cents(7); 		// anonymous object
```

In C++, anonymous objects are primarily used either to pass or return values without having to create lots of temporary varaibles to do so. Memory allocated dynamically is also done so anonymously.
However, it is worth noting that anonymous objects are treated as rvalues (not lvalues, which have an address) -- therefore, all rules about passing and returning rvalues apply.
It is also worth noting that because anynomous objects have expression scope, they can only be used once. If you need to reference a value in multiple expressions, you should use a named variable instead.
