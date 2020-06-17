#Basic inheritance in C++
Inheritance in C++ takes place between classes. In an inheritance (is-a) relationship, the class being inherited from is called the **parent class, base class, or superclass**, and the class doing the inheriting is called the **child class, derived class, or subclass**.
```cpp
#include <string>
class Person {
public:
	std::string m_name;
	int m_age;
	Person(std::string name = "", int age = 0) : m_name(name), m_age(age){}
	std::string getName() const {return m_name;}
	int getAge() const {return m_age;}
};

class BaseballPlayer : public Person {
public:
	double m_battingAverage;
	int m_homeRuns;
	BaseballPlayer(double battingAverage = 0.0, int homeRuns=0) : m_battingAverage(battingAverage), m_homeRuns(homeRuns){}
};

class Employee: public Person {
public:
	double m_hourlySalary;
	long m_employeeID;
	Employee(double hourlySalary = 0.0, long employeeID = 0) : m_hourlySalary(hourlySalary), m_employeeID(employeeID){}
	void printNameAndSalary() const {
		std::cout << m_name << ": " << m_hourlySalary << '\n';
	}
}
```
####Inheritance chains
It's possible to inherit from a class that is itself derived from another class.

Inheriting from a base class means we don't have to redefine the information from the base class in our derived classes. We automatically receive the member functions and member variables of the base class through inheritance, and then simply add the additional functions or member variables we want.


###Order of construction of derived classes
When C++ constructs derived objects, it does so in phases. First, the most-base class (at the top of the inheritance tree) is constructed first. Then each child class is constructed in order, until the most-child class (at the bottom of the inheritance tree) is constructed last.

##Constructors and initizliation of derived classes
1. Memory for derived is set aside (enough for both the Base and Derived portions)
2. The appropriate Derived constructor is called.
3. **The base object is constructed first using the appropriate Base constructor**. If no base constructor is specified, the default constructor will be used.
4. The initialization list initializes variables
5. The body of the constructor executes
6. Control is returned to the caller

C++ prevents classes from initializing inherited member variables in the initialization list of a constructor. In other words, the value of a variable can only be set in an initialization list of a constructor belonging to the same class as the variable.

Because const variables must be initialized with a value at the time of creation, the base class constructor must set its value when the variable is created.
However, when the base class constructor finishes, the derived class constructors initialization lists are then executed.
Each derived class would then have the opportunity to initialize that variable, potentially changing its value! By restricting the initialization of variables to the constructor of the class those variables belong to, C++ ensures that all variables are initialized only once.

C++ gives us the ability to explicitlyj choose which base class constructor will be called. To do this, simply add a call to the base class Constructor in the initialization list of the derived class:
```cpp
class Derived : public Base {
public:
	double m_cost;
	Derived (doubel cost = 0.0; int id = 0) : Base{id}, m_cost{cost}{}
	double getCost() const {return m_cost;}
}
```
Here's what happens:
1. Memory for derived is allocated
2. The Derived(double, int) constructor is called
3. The compiler looks to see if we've asked for a particular Base class constructor.
4. The base class constructor initialization list sets `m_id`
5. The base class constructor body executes, which does nothing
6. The base class constructor returns
7. The derived class constructor initialization list sets `m_cost`
8. The derived class constructor body executes, which does nothing
9. The derived class constructor returns

####Inheritance chains
Classes in an inheritance chain work in exactly the same way.

####Destructors
When a derived class is destroyed, each destructor is called in the reverse order of construction
