#Function templates
In C++, **function templates** are functions that serve as a pattern for creating other similar functions. The basic idea behind function template is to create a function without having to specify the exact type(s) of some or all of the variables.
Instead, we define the function using placeholder types, called **template type parameters**. Once we have created a function using these placeholder types, we have effectively created a "function stencil".

####Creating function templates in C++
1. Template definition.
2. A placeholder type

```cpp
template <typename T>	// this is the template parameter declaration
T max(T x, T y) {
	return (x > y) ? x : y;
}
```
If the template function uses multiple template type parameter, they can be separated by commas:
```cpp
template <typename T1, typename T2>
// template function here
```
Because the function argument passed in for type T could be a class type, and it's generally not a good idea to pass classes by value, it would be better to make the parameters and return types of our templated function const references:
```cpp
template <typename T>
const T& max(const T& x, const T& y) {
	return (x > y) ? x : y;
}
```

Template functions do have a few drawbacks:
1. Some older compilers do not have very good template support.
2. Template functions often produce carzy-looking error messages that are much harder to decipher than those regular functions.
3. Template functions can increase your compile time and code size, as a single template might be "realized" adn recompiled in many files.
