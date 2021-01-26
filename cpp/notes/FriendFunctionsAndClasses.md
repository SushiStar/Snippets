#Friend Functions and Classes
##Friend functions
A **friend function** is a function that can access the private members of a class as though it were a member of that class. In all other regards, the friend function is just like a normal function. A friend function may be either a normal function, or a member function of another class. To declare a friend function, simply use the *friend* keyword in front of the prototype of the function you wish to be a friend of the class. It does not matter whether you declare the friend function in the private or public section of the class.
**Example**
```cpp
class Accumulator {
private:
	int m_value;
public:
	Accumulator() {m_value = 0;}
	void add(int value) {m_value += value;}

	// make the reset() function a friend of this class
	friend void reset(Accumulator &accumulator);
};

// reset() is now a friend of the Accumulator class
void reset(Accumulator &accumulator) {
	// And can access the private data of Accumulator objects
	accumulator.m_value = 0;
}

int main() {
	Accumulator acc;
	acc.add(5);
	reset(acc);
	return 0;
}
```
Note that we have to pass an Accumulator object to `reset()`. This is because `reset()` is not a member function. It does not have a `*this` pointer, nor does it have an Accumulator object to work with, unless given one.

###Multiple friends
A function can be a friend of more than one class at the same time.
**Example**
```cpp
#include <iostream>
class Humidity {
private:
	int m_humidity;
public:
	Humidity(int humidity=0) : m_humidity(humidity){}
	friend void printWeather(const Temperature &temperature, const Humidity &humidity);
};

class Temperature {
private:
	int m_temp;
public:
	Temperature(int temp=0) : m_temp(temp){}
	friend void printWeather(const Temperature &temperature, const Humidity &humidity);
};

void printWeather(const Temperature &temperature, const Humidity &humidity) {
	std::cout << "The temperature is " << temperature.m_temp <<
	" and the humidity is " << humidity.m_humidity << '\n';
}
```
> 1) Because PrintWeather is a friend of both classes, it can access the private data from objects of both classes.
> 2) Class prototypes serve the same role as function prototypes -- they tell the compiler what something looks like so it can be used now and defined later.

##Friend classes
It is also possible ot make an entire class a friend of another class. This gives all of the members of the friend access to private members of the other class.
```cpp
#include<iostream>
class Storage {
private:
	int m_nValue;
	double m_dValue;
public:
	Storate(int nValue, int dValue) : m_nValue(nValue), m_dValue(dValue){}
	// Make the Display class a friend of Storage
	friend class Display;
};

class Display {
private:
	bool m_displayIntFirst;
public:
	Display(bool displayIntFirst) : m_displayIntFirst(displayIntFirst){}
	void displayItem(const Storage &storage) {
		if (m_displayIntFirst)
			std::cout << storage.m_nValue << " " << storage.m_dValue << '\n';
		else	// display double first
			std::cout << storage.m_dValue << " " << storage.m_nValue << '\n';
	}
};
```
- Even though Display is a friend of Storage, Display has no direct access to the `*this` pointer of Storage objects.
- Just because Display is a friend of Storage, that does not mean Storage is also a friend of Display. If you want two classes to be friends of each other, both must declare the other as friend.
- If class A  is a friend of B, and B is a friend of C, that does not mean A is a friend of C.

##Friend member functions
Instead of making an entire class of a friend, you can make a single member function a friend.
In order to make a member function a friend, the compiler has to have seen the full definition for the class of the friend member function (not just a forward declaraction).
```cpp
#include <iostream>
class Storage;			// forward declaraction for class Storage.
class Display {
private:
	bool m_displayIntFirst;
public:
	Display(bool displayIntFirst) : m_displayIntFirst(displayIntFirst){}
	void displayItem(const Storage &storage); 	// forward declaraction above needed for this declaration
};
class Storage {
private:
	int m_nValue;
	double m_dValue;
public:
	Storage(int nValue, double dValue) : m_nValue(nValue), m_dValue(dValue){}
	// make the Display::displayItem member function a friend of the Storage class
	friend void Display::displayItem(const Storage &storage);
};

void Display::displayItem(const Storage &storage) {
	if (m_displayIntFirst)
		std::cout << storage.m_nValue << " " << storage.m_dValue << '\n';
	else	// display double first
		std::cout << storage.m_dValue << " " << storage.m_nValue << '\n';
}
```
