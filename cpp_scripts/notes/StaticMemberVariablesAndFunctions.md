#Static member variables and functions
##Static member varialbes
Member variables of a class can be made static by using the `static` keyword. Unlike normal membver varialbes, static member variables are shared by all objects of the class.
```cpp
class Something {
public:
    static int s_value;
};
 
int Something::s_value{ 1 };
 
int main()
{
    Something first;
    Something second;
 
    first.s_value = 2;
 
    std::cout << first.s_value << '\n';
    std::cout << second.s_value << '\n';
    return 0;
}
```
###Static members are not associated with class objects**
Although you can access static members through objects of the class (as shown with `first.s_value`), it turns out that static member exist even if no objects of the class have been instantiated. Much like global variables, they are created when the program starts, and destoryed when the program ends.
Consequently, it is better to think of static members as belonging to the class itself, not to the objects of the class.
```cpp
class Something {
public:
    static int s_value; // declares the static member variable
};
 
int Something::s_value{ 1 }; // defines the static member variable (we'll discuss this section below)
 
int main()
{
    // note: we're not instantiating any objects of type Something
 
    Something::s_value = 2;
    std::cout << Something::s_value << '\n';
    return 0;
}
```
###Defining and Initizlizing static member variables
When we declare a static member variable inside a class, we're telling the compiler about the existence of a static member variable, but not actually defining it. Because static member variables are not part of the individual class objects, you must explicitly define the static member outside of the class, in the global scope.
In the example above, we do so via this line:
```cpp
int Something::s_value{1};
```
This line serves two purposes: it instantiates the static member variable (just like a global variable), and optionally initializes it.
Note that this static member definition is not subject to access controls: you can define and initialize the value even if it's decalred as private in the class.
Do not put the static member definition in a header file, if that header file gets included more than once, you'll end up with multiple definitions, which will cause a compiler error.

###Inline initialization of static member variables
When the static member is a const integral type (which includes char and bool) or a const enum, the static member can be initilized inside the class definition:
```cpp
class Whatever {
public:
	static const int s_value{4};	// a static const int can be decalred and initizlized directly
};
```
Static constexpr members can be initialized inside the class definition:
```cpp
class Whatever {
public:
	static constexpr double s_value{2.2};
	static constexpr std::array<int, 3> s_array{1, 2, 3};
};
```
##Static member functions
Normally we access private members from public member functions. While we could create a normal public member function to access `s_value`, we'd then need to instantiate an object of the class type to use the function.
Like static member variables, static member functions are not attahced to any particular object.
```cpp
class Something
{
private:
    static int s_value;
public:
    static int getValue() { return s_value; } // static member function
};
 
int Something::s_value{ 1 }; // initializer
 
int main()
{
    std::cout << Something::getValue() << '\n';
}
```
Because static member functions are not attached to a particular object, they can be called directly by using the class name and the scope resolution operator.
###Static member functions have no \*this pointer
###A word of warning about classes with all static members
Be careful when writing classes with all static members. Although such "pure static classes" can be useful, they also come with some potential downsides.
First, because all static members are instantiated only once, there is no way to have multiple copies of a pure static class.
Second, because all of the members belong to the class, and class declarations usually have global scope, a pure static class is essentially teh equivalent of declaring functions and global variables in a globally accessible namespaces.

###C++ does not support static constructors
