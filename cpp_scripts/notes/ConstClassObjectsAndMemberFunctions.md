#Const class objects and member functions
##Const classes
Instantiated class objects can be made const by using the const keyword.
##Const member functions
A const member function is a member function that guarantees it will not modify the object or call any non-const member functions (as they may modify the object).
```cpp
class Something {
public:
	int m_value;
	Something() : m_value(0){}
	void resetValue() {m_value = 0;}
	void setValue(int value) {m_value = value;}
	int getValue() const {return m_value;}
}
```
Now `getValue()` has been made a const member function, which means we can call it on any const objects.
For functions defined outside of the class definition, the const keyword must be used on both the function prototype in the class definition and on the function definition.
Furthermore, any const member function that attempts to change a member variable or call a non-const member function will cause a compiler error to occur.
>**Rule**
>Make any member function that does not modify the state of the class object const, so that it can be called by const objects.

##Const references
##Overloading const and non-const function
Although it is not done very often, it is possible to overload a function in such a way to have a const and non-const version of the same function:
```cpp
#include <string>

class Something {
private:
	std::string m_value;
public:
	Something(const std::string &value="") : m_value{value} {}
	const std::string& getValue() const {return m_value;}	// getValue() for const object
	std::string& getValue() {return m_value;}	// getValue() for non-const objects
}

int main() {
	Something something{};
	something.getValue() = "Hi";		// calls non-const getValue();

	const Something something2{};
	something2.getValue(); 				// calls const getValue();
}
```
The const version will be called on any const objects, and the non-const version will be called on any non-const objects.
Overloading a function with a const and non-const version is typically done when the return value needs to differ in constness. 
