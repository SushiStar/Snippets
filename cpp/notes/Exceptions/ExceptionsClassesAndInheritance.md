#Exceptions, classes, and inheritance
####Exceptions and member functions
If a constructor must fail for some reason (e.g. the user passed in invalid input), simply throw an exception to indicate the object failed to create. In such a case, the object's construction is aborted, and all class members (which have already been created and initizlied prior to the body of the constructor executing) are destructed as per usual. However, the class's destructor is never called (because the object never finished construction).
####Exceptions classes
An exception class is just a normal class that is designed specifically to be thrown as an exception.
```cpp
class ArrayException {
private:
	std::string m_error;

public:
	ArrayException(std::string error) : m_error(error) {}
	 const char* getError() const { return m_error.c_str(); }
};

class IntArray {
private:

	int m_data[3]; // assume array is length 3 for simplicity
public:
	IntArray() {}

	int getLength() const { return 3; }

	int& operator[](const int index) {
		if (index < 0 || index >= getLength())
			throw ArrayException("Invalid index");
		return m_data[index];
	}
};

int main()
{
	IntArray array;

	try {
		int value{ array[5] };
	} catch (const ArrayException &exception) {
		std::cerr << "An array exception occurred (" << exception.getError() << ")\n";
	}
}
```
Using such a class, we can have the exception return a description of the problem that occurred, which provides context for what went wrong. And since ArrayException is its own unique type, we can specifically catch exceptions thrown by the array class and treat them differently from other exceptions if we wish.
Note that exception handlers should catch class exception objects by reference instead of by value. This prevents the compiler from making a copy of the exception, which can be expensive when the exception is a class object, and prevents object slicing when dealing with derived exception classes (which we’ll talk about in a moment). Catching exceptions by pointer should generally be avoided unless you have a specific reason to do so.

####`std::exception`
`std::exception` is a small interface class designed to serve as a base class to any exception thrown by the C++ standard library.
```cpp
int main() {
	try {
		// Your code using standard library goes here
		// We'll trigger one of these exceptions intentionally for the sake of example
                std::string s;
                s.resize(-1); // will trigger a std::length_error
	} // This handler will catch std::exception and all the derived exceptions too
	catch (const std::exception &exception) {
		std::cerr << "Standard exception: " << exception.what() << '\n';
	}
	return 0;
}
```
The one thing worth noting is that `std::exception` has a virtual member function named `what()` that returns a C-style string description of the exception. Most derived classes override the `what()` function to change the message.

####Using the standard exceptions idrectly
