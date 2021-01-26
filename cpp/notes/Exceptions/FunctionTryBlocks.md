#Function try blocks
Function try blocks are designed to allow you to establish an exception handler around the body of an entire function, rather than around a block of code.
```cpp
class A {
private:
	int m_x;
public:
	A(int x) : m_x(x) {
		if (x <= 0)
			throw 1;
	}
};

class B : public A
{
public:
	B(int x) try : A(x) // note addition of try keyword here { }
	catch (...) // note this is at same level of indentation as the function itself
	{
                // Exceptions from member initializer list or constructor body are caught here

                std::cerr << "Exception caught\n";

                // If an exception isn't explicitly thrown here, the current exception will be implicitly rethrown
	}
};

int main()
{
	try
	{
		B b(0);
	}
	catch (int)
	{
		std::cout << "Oops\n";
	}
}
```
####Exceptions and destructors
Unlike constructors, where throwing exceptions can be a useful way to indicate that object creation did not succeed, exceptions should never be thrown in destructors.

The problem occurs when an exception is thrown from a destructor during the stack unwinding process. If that happens, the compiler is put in a situation where it doesn’t know whether to continue the stack unwinding process or handle the new exception. The end result is that your program will be terminated immediately.
Consequently, the best course of action is just to abstain from using exceptions in destructors altogether. Write a message to a log file instead.

####Performance concerns
Exceptions do come with a small performance price to pay. They increase the size of your executable, and they may also cause it to run slower due to the additional checking that has to be performed. However, the main performance penalty for exceptions happens when an exception is actually thrown. In this case, the stack must be unwound and an appropriate exception handler found, which is a relatively expensive operation.

Exception handling is best used when all of the following are true:
- The error being handled is likely to occur only infrequently.
- The error is serious and execution could not continue otherwise.
- The error cannot be handled at the place where it occurs.
- There isn’t a good alternative way to return an error code back to the caller.
