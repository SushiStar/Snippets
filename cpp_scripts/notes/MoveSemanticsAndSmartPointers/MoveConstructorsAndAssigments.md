#Move constructors and move assignments
####Copy constructors and copy assigments
Copy constructors are used to initialize a class by making a copy of an object of the same class. Copy assignment is used to copy one class to another existing class.
####Move constructors and move assigments
C++11 defines two new functions in service of move semantics: a move constructor, and a move assignment operator. Whereas the goal of the copy constructor and copy assignment is to make a copy of one object to another, the goal of the move constructor and move assignment is to move ownership of the resources from one object to another (which is much less expensive than making a copy).

Defining a move constructor and move assignment work analogously to their copy counterparts. However, whereas the copy flavors of these functions take a const l-value reference parameter, the move flavors of these functions use non-const r-value reference parameters.
```cpp
template<class T>
class Auto_ptr4 {
	T* m_ptr;
public:
	Auto_ptr4(T* ptr = nullptr) :m_ptr(ptr) {}
	~Auto_ptr4() {
		delete m_ptr;
	}

	// Copy constructor
	// Do deep copy of a.m_ptr to m_ptr
	Auto_ptr4(const Auto_ptr4& a) {
		m_ptr = new T;
		*m_ptr = *a.m_ptr;
	}

	// Move constructor
	// Transfer ownership of a.m_ptr to m_ptr
	Auto_ptr4(Auto_ptr4&& a) : m_ptr(a.m_ptr) {
		a.m_ptr = nullptr; // we'll talk more about this line below
	}

	// Copy assignment
	// Do deep copy of a.m_ptr to m_ptr
	Auto_ptr4& operator=(const Auto_ptr4& a) {
		// Self-assignment detection
		if (&a == this)
			return *this;

		// Release any resource we're holding
		delete m_ptr;

		// Copy the resource
		m_ptr = new T;
		*m_ptr = *a.m_ptr;

		return *this;
	}

	// Move assignment
	// Transfer ownership of a.m_ptr to m_ptr
	Auto_ptr4& operator=(Auto_ptr4&& a) {
		// Self-assignment detection
		if (&a == this)
			return *this;

		// Release any resource we're holding
		delete m_ptr;

		// Transfer ownership of a.m_ptr to m_ptr
		m_ptr = a.m_ptr;
		a.m_ptr = nullptr; // we'll talk more about this line below

		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};

class Resource {
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};

Auto_ptr4<Resource> generateResource() {
	Auto_ptr4<Resource> res(new Resource);
	return res; // this return value will invoke the move constructor
}

int main() {
	Auto_ptr4<Resource> mainres;
	mainres = generateResource(); // this assignment will invoke the move assignment
	return 0;
}
```
The move constructor and move assignment operator are simple. Instead of deep copying the source object (a) into the implicit object, we simply move (steal) the source object’s resources. This involves shallow copying the source pointer into the implicit object, then setting the source pointer to null.

####When are the move constructor and  move assignment called?
The move constructor and move assignment are called when those functions have been defined, and the argument for construction or assignment is an r-value. Most typically, this r-value will be a literal or temporary value.
In most cases, a move constructor and move assignment operator will not be provided by default, unless the class does not have any defined copy constructors, copy assignment, move assignment, or destructors.

If we construct an object or do an assignment where the argument is an l-value, the only thing we can reasonably do is copy the l-value. We can’t assume it’s safe to alter the l-value, because it may be used again later in the program. If we have an expression “a = b”, we wouldn’t reasonably expect b to be changed in any way.

However, if we construct an object or do an assignment where the argument is an r-value, then we know that r-value is just a temporary object of some kind. Instead of copying it (which can be expensive), we can simply transfer its resources (which is cheap) to the object we’re constructing or assigning. This is safe to do because the temporary will be destroyed at the end of the expression anyway, so we know it will never be used again!

####Automatic l-values returned by value may be moved instead of copied
The C++ specification has a special rule that says automatic objects returned from a function by value can be moved even if they are l-values. This makes sense, since res was going to be destroyed at the end of the function anyway! We might as well steal its resources instead of making an expensive and unnecessary copy.

