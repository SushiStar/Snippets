# Chapter11: Select Operations
## Etc. Operators
- The bitwise logical operators: & | ^ ~ >> and << are applied to objects of integral types(char, short, int, long, long long, unsigned\*\*, bool, wchar\_t, char16\_t, char32\_t).
- The operators ++ and -- can be used as both prefix and postfix operators.
The value of ++x is the new (that is, incremented) value of x.
The value of x++ is the old value of x. 
~~~
    // copy a string
    while(*p++ = *q++){}
~~~
However, the most efficient way of copying a zero-terminated character string is typically the standard C-style string copy function.
~~~
    char* strcpy(char*, const char*); // from <string.h>
~~~
Whenever possible, use standard-library facilities in preference to fiddling with pointers and bytes.

## Free Store
- Objects allocated by new are said to be "on the free store" (also, "on the heap" or "in dynamic memory").
If a type has a default constructor, we can leave out the initializer, but bulit-in types are by default uninitialized.
~~~
    auto pc = new complex<double; // the complex is initialized to {0,0}
    auto pi = new int;            // the int is uninitialized
~~~
To be sure to get default initialization, use{}.
~~~
    auto pc = new complex<double>{}; // the complex is initialized to {0,0}
    auto pi = new int{};             // the int is initialzied to 0
~~~
- An object created by **new** exists until it is explicitly destoryed by **delete**.
If deleted object if of a class with a destructor, that destructor is called by **delete** before the object's memory is released for reuse.
- The main problems wiht free store are:
    * Leaked objects: People use **new** and then forget to **delete** the allocated object.
    * Premature deletion: People **delete** an object that they have some other pointer to adn later use that other pointer.
    * Double deletion: An object is deleted twice, invoking its destructor (if any) twice. In general, a double deletion is undefined  behavior and the results are unpredictable and usually disastrous.
- Approaches of resource management:
    * Don't put objects on the free store if you don't have to; prefer scoped variables.
    * When you construct an object on the free store, place its pointer into a manager object with a destructor that will destory it. Whenever possible, have that manager object be a scoped variable.
- **new** belongs in constructors and similar operations, **delete** belongs in destructors, and together they provide a coherent memory management strategy.
- Do not use **new** to create local object.
- These <span style='color:blue'>**operator new**</span> functions return nullptr, rather than throwing <code>bad\_alloc</code>, if there is not sufficient memory to allocate.

## Lambda Expression
- A lambda expression, is a simplified notation for defining and using an object of that function object.
This is expecially usefull when we want to pass an operation as an argument to an algorithm, such operations are often referred to as callbacks.
- A lambda might outlive its caller.

## Explicit Type Conversion
~~~
    template<typename Target, typename Source>
    Target narrow_cast(Source v) {
        auto r = static_cast<Target>(v);
        if(stati_cast<Source>(r) != v)
            throw runtime_error("narrow_cast<>() failed");
        return r;
    }
~~~
Prefer T{v} conversions for well-behaved construction and the named casts (e.g., static\_cast) for other conversions.
