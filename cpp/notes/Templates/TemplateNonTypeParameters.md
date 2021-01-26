#Template non-type parameters
Template classes and functions can make use of another kind of template parameter known as a non-type parameter.
####Non-type parameters
A template non-type parameter is a special type of parameter that does not substitute for a type, but is instead replaced by a value. A non-type parameter can be any of the following:
- A value that has an integral type or enumeration
- A pointer or reference to a class object
- A pointer or reference to a function
- A pointer or reference to a class member function
- `std::nullptr_t`
In the following example, we create a non-dynamic (static) array that uses both a type parameter and a non-type parameter. The type parameter controls the data type of the static array, and the non-type parameter controls how large the static array is.
```cpp
template <class T, int size> // size is the non-type parameter
class StaticArray {
private:
    // The non-type parameter controls the size of the array
    T m_array[size];

public:
    T* getArray();

    T& operator[](int index) {
        return m_array[index];
    }
};

// Showing how a function for a class with a non-type parameter is defined outside of the class
template <class T, int size>
T* StaticArray<T, size>::getArray() {
    return m_array;
}
```
####Function template specialization
```cpp
template <class T>
class Storage {
private:
    T m_value;
public:
    Storage(T value) {
         m_value = value;
    }

    ~Storage() {}

    void print() {
        std::cout << m_value << '\n';
    }
};
```
Now, let's say we want double values (and only double values) to output in scientific notation. To do so, we can use a **function tempalte specialization** (sometimes called a full or explicit function template specialization) to create a specialized version of the `print()` function for type double.
Simply define the specialized function (if the function is a member function, do so outside of the class definition), replacing the template type with the specific type you wish to redefine the function for.
```cpp
template <>
void Storage<double>::print() {
    std::cout << std::scientific << m_value << '\n';
}
```
When the compiler goes to instantiate `Storage<double>::print()`, it will see we’ve already explicitly defined that function, and it will use the one we’ve defined instead of stenciling out a version from the generic templated class.
The `template <>` tells the compiler that this is a template function, but that there are no template parameters (since in this case, we’re explicitly specifying all of the types).
Some compilers may allow you to omit this, but it's proper to include it.
