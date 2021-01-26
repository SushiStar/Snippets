# Classes
Using the `class` keyword defines a new user-defined type called a class.
In fact struct and class are effectively identical, the only significant difference is the `public`: keyword in the class. 

###Member functions
Functions defined inside of a class are called member functions.
>**Rule**
>Name your classes starting with a captial letter.

### Member types
In addition to member variables and member functions, `class`es can have member types or nested types (including typing aliases).

### A note about structs in C++
In C, structs can only hold data, and do not have associated member functions.
In C++, it's fair to assume a class will clean up after itself, but it's not safe to assume a struct will. Consequently, we recommend using the struct keyword for data-onoly structures, and the class keyword for defining objects that have both data and functions.

### Public vs private access specifiers
Public members are members of a struct or class that can be accessed from outside the struct or class. Private members are members of a class taht can only be accessed by other members of the class.
Although class members are private by default, we can make them public by using the public keyword.
Access specifiers determine who has access to the members that follow the specifier.

### Mixing access specifiers
A class can (and almost always does) use multiple access specifiers to set the access levels of each its members.
There is no limit to the number of access specifiers you can use in a class.
In general, member variables are usually made private, and member functions are usually made public.

>**Rule**
>Make member variables private, and member functions public, unless you have a good reason not to.

### Access controls work on a per-class basis
One nuance of C++ that is often missed of misunderstood is that access control works on a per-class basis, not a per-object basis. This means that when a function has access to the private members of a class, it can access the private members of any object of that class type that it can see:

```cpp
#include <iostream>
 
class DateClass // members are private by default
{
	int m_month; // private by default, can only be accessed by other members
	int m_day; // private by default, can only be accessed by other members
	int m_year; // private by default, can only be accessed by other members
 
public:
	void setDate(int month, int day, int year)
	{
		m_month = month;
		m_day = day;
		m_year = year;
	}
 
	void print()
	{
		std::cout << m_month << '/' << m_day << '/' << m_year;
	}
 
	// Note the addition of this function
	void copyFrom(const DateClass &d)
	{
		// Note that we can access the private members of d directly
		m_month = d.m_month;
		m_day = d.m_day;
		m_year = d.m_year;
	}
};
 
int main()
{
	DateClass date;
	date.setDate(10, 14, 2020); // okay, because setDate() is public
	
	DateClass copy;
	copy.copyFrom(date); // okay, because copyFrom() is public
	copy.print();
 
	return 0;
}
```
### Structs vs classes revisited
A class defaults its members to private. A struct defaults its members to public.