Constructors

A constructor is a special kind of class member function that is automatically called when an object of that class is instantiated. Constructors are typically used to initialize member variables of the class to appropriate default or user-provided values, or to do any setup steps necessary for the class to be used.
Unlike normal member functions, constructors have specific rules for how htey must be named:

1. Constructors must have the same name as the class (with the same capitalization)
2. Constructors have no return type (not even void)

### Default constructors
A constructor that takes no parameters (or has parameters that all have default values) is called a default constructor. The default constructor is called if no user-provided initialization values are provided.

### Direct and uniform initialization using constructors with parameters

```cpp
Fraction fiveThirds{5, 3};      // Brace initialization, calls Fraction(int, int)
Fraction threeQuarters(3, 4);   // Direct initialization, also calls Fraction(int, int)
```
Since C++11, we prefer brace initialization. There is another special constructor that might take brace initialization do something different, in that case we have to use direct initialization.

## Copy initialization using equals with classes
### Reducing your constructors
The default constructor is actualy somewhat redundant. And it could be simplified as follows:

```cpp
#include <cassert>
class Fraction {
private:
    int m_numerator;
    int m_denominator;

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1) {
        assert(denominator!=0);

        m_numerator = numerator;
        m_denominator = denominator;
    }
    int getNumerator() {return m_numerator;}
    int getDenominator() {return m_denominator;}
    double getValue() {return static_cast<double>(n_numerator)/m_denominator;}
}
```
### A reminder about default parameters
When defining a function with default parameters, all default parameters must follow any non-default parameters, ie. there cannot be a non-defaulted parameter after a defaulted parameter.

### An implicitly generated default constructor
If your class has no constructors, C++ will automatically generate a public default constructor for you. This is sometimes called an implicit constructor.
Implicit constructor allows us to create an object with no arguments, but doesn't initialize any of the built-in members, because they are fundamental types and those don't get initialized upon creation.
To make sure the member variables get initialized, we can initialize them at their declaration:

```cpp
class Date {
private:
    int m_year{1900};
    int m_month{1};
    int m_day {1};
}
```
**If your class has any other constructors, the implictly generated constructor will not be provided.**

```cpp
class Date
{
private:
    int m_year{ 1900 };
    int m_month{ 1 };
    int m_day{ 1 };
 
public:
    Date(int year, int month, int day) // normal non-default constructor
    {
        m_year = year;
        m_month = month;
        m_day = day;
    }
 
    // No implicit constructor provided because we already defined our own constructor
};
 
int main()
{
    Date date{}; // error: Can't instantiate object because default constructor doesn't exist and the compiler won't generate one
    Date today{ 2020, 1, 19 }; // today is initialized to Jan 19th, 2020
 
    return 0;
}
```
To allow construction of a `Date` without arguments, either add default arguments to the constructor, andd an empty default constructor, or explicitly add a default constructor:
```cpp
Date() = default;
```
Using `= default` is almost the same as adding a default constructor with an empty body. The only difference is that `= default` allows us the safely initialize member variables even if the don't have an initializer.
Using `= defalut` may be longer than writing a constructor with an empty body, but expresses better what your intentions are (To create a default constructor), and it's safer.
>**Rule**
>If you have constructors in your class and need a default constructor that does nothing, use `= default`.

### Classes containing classes
A `class` may contain other classes as member variables. By default, when the outer class is constructed, the member variables will have their deafult constructors called. The happens before the body of the constructor executes.

### Constructor notes
Constructors actually serves two purposes. First, constructors determine who is allowed to create an object. That is, an object of a class can only be created if a matching constructor can be found.
Second, constructors can be used to initialize objects. Whether the constructor actually does an initialization is up to the programmer. It's syntactically valid to have a constructor that does no initialization at all (the constructor still serves teh purpose of allowing the object to be created, as per above).

## Constructor member initializer lists
### Member initializer lists
C++ provides a method for initializing class member variables (rather than assigning values to them after they are created) via a member initializer list.

```cpp
class Something
{
private:
    int m_value1;
    double m_value2;
    char m_value3;
 
public:
    Something() : m_value1{ 1 }, m_value2{ 2.2 }, m_value3{ 'c' } // Initialize our member variables
    {
    // No need for assignment here
    }
 
    void print()
    {
         std::cout << "Something(" << m_value1 << ", " << m_value2 << ", " << m_value3 << ")\n";
    }
};
 
int main()
{
    Something something{};
    something.print();
    return 0;
}
```
>**Rule**
>Use member initializer lists to initialize your class member variables instead of assignment.

### Formatting your initializer list
If the initializer list fits on the same line as the function name, then it's fine to put everything on one line.
If the initializer list doesn't fit on the same line as the funciton name, then it should go indented on the next line.
If all of the initializers don't fit on a single line (or the initializers are non-trivial), then you can space them out, one per line.

### Initializer list order
Variables in the initializer list are not initialized in the order that they are specified in the initilizer list. Instead, they are initialized in the order in which they are declared in the class.
For best results, the following recommendations should be observed:

1. Don't initialize member variables in such a way that they are dependent upon other member variables being initialized first (in other words, ensure your member variables will properly initialize even if the initialization ordering is different).
2. Initialize variables in the initializer list in the same order in which they are declared in your class. This isn't strictly required so long as the prior recommendation has been followed, but your compiler may give you a warning if you don't do so and you have all warnings turned on.

## Non-static member initialization
Non-static member initialization (also called in-class initializers) provide default values for your member variables that your constructors will use if the constructors do not provide initialization values for the members themselves (via the member initialization list).
If a default initialization value is provided and the constructor initializes the member via the member initializer list, the member initializer list will take precedence.

```cpp
#include <iostream>
 
class Rectangle
{
private:
    double m_length{ 1.0 };
    double m_width{ 1.0 };
 
public:
 
    Rectangle(double length, double width)
        : m_length{ length },
          m_width{ width }
    {
        // m_length and m_width are initialized by the constructor (the default values aren't used)
    }
 
    Rectangle(double length)
        : m_length{ length }
    {t
        // m_length is initialized by the constructor.
        // m_width's default value (1.0) is used.
    }
 
    void print()
    {
        std::cout << "length: " << m_length << ", width: " << m_width << '\n';
    }
 
};
```
# Overlapping and delegating constructors
### Constructors with overlapping functionality
With a pre-C++11 compiler, if you try to have one constructor call another constructor, it will often compile, but it will not work as you expected, and you will likely spend a long time trying to figure out why, even with a debugger.
### Using a spearate function
Constructors are allowed to call non-constructor functions in class.
The best solution is to create a non-constructor function that does the common initialization, and have both constructors call that funciton.

```cpp
class Foo {
private:
    void DoA() {
        // code to do A
    }
public:
    Foo() {
        DoA();
    }
 
    Foo(int nValue) {
        DoA();
        // code to do B
    }
};
```
It is fairly common to include an `Init()` function that initializes member variables to their default values, and then have each constructor call that `Init()` function before doing its parameter-specific tasks. This minimizes code duplication and allows you to explicitly call `Init()` from wherever you like.
One small caveat: be careful when using Init() functions and dynamically allocated memory. Because Init() functions can be called by anyone at any time, dynamically allocated memory may or may not have already been allocated when `Init()`  is called.

### Delegating constructors in C++11
Starting with C++11, constructors are now allowed to call other constructors. This process is called delegating constructors (or constructor chaining):

```cpp
class Foo {
private:
public:
    Foo() {
        // code to do A
    }

    Foo(int value):Foo() {  // use Foo() constructor to do A
        // code to do B
    }
};
```
This works exactly as you'd expected. **Make sure you're calling the constructor from the member initializer list, not in the body of the constructor.**
Another example:

```cpp
#include <string>
#include <iostream>
 
class Employee {
private:
    int m_id;
    std::string m_name;
 
public:
    Employee(int id=0, const std::string &name=""):
        m_id(id), m_name(name) {
        std::cout << "Employee " << m_name << " created.\n";
    }
    // Use a delegating constructor to minimize redundant code
    Employee(const std::string &name) : Employee(0, name) { }
};

```
A few additional notes about delegating constructors. First, a constructor that delegates to another constructor is not allowed to do any member initialization itself. So you constructor can delegate or initialize, but not both.
Second, it's possible for one constructor to delegate to another constructor, which delegates back to the first constructor. This forms an infinite loop, and will cause your program to run out of stack space and crash. You can avoid this by ensuring all of your constructors resolve to a non-delegating constructor.
