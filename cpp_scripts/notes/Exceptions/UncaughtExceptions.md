#Uncaught exceptions, catch-all handlers, and exception sepcifiers

####Uncaught exceptions
The program just terminates

####Catch-all handlers
C++ provides us with a mechanism to catch all types of exceptions. This is known as a **catch-all handler**. A catch-all handler works just like a normal catch block, except that instead of using a specific type to catch, it uses the ellipses operator (...) as the type to catch.
```cpp
int main() {
	try {
		throw 5; // throw an int exception
	}
	catch (double x) {
		std::cout << "We caught an exception of type double: " << x << '\n';
	}
	catch (...) { // catch-all handler
		std::cout << "We caught an exception of an undetermined type\n";
	}
}
```
Because there is no specific exception handler for type int, the catch-all handler catches this exception.
The catch-all handler should be placed last in the catch block chain.

####Using the catch-all handler to wrap main()

####Nonexcept
Nonexcept is a exception specifier that is used to indicate that a function can not throw an exception. Semantically, it allows you to see at a glance that a function will not throw an exception.
It also potentially enables some compiler optimizations. Destructors are generally implicitly noexcept (as they can't throw an exception). If a nonexcept function does try to throw an exception, then `std::terminate` is called to terminate the application.
