#Intro to smart pointers and move semantics
```cpp
void someFunction() {
    Resource *ptr = new Resource;
    int x;
    std::cout << "Enter an integer: ";
    std::cin >> x;
    if (x == 0)
        throw 0; // the function returns early, and ptr won’t be deleted!
    // do stuff with ptr here
    delete ptr;
}
```
In the above program, the early return or throw statement execute, causing the function to terminate without variable ptr being deleted. Consequently, the memory allocated for variable ptr is now leaked (and will leak again every time this function is called and returns early).

One of the best things about classes is that they contain destructors that automatically get executed when an object of the class goes out of scope.

A **Smart pointer** is a composition class that is designed to manage dynamically allocated memory and ensure that memory gets deleted when the smart pointer object goes out of scope.
####Move semantics
**Move semantics** means the class will transfer ownership of the object rather making a copy.
####`std::auto_ptr`, and why to avoid it
`std::auto_ptr`, introduced in C++98, was C++'s first attempt at a standardized smart pointer.
1. Because `std::auto_ptr` implements move semantics through the copy constructor and assignment operator, passing a `std::auto_ptr` by value to a function will cause your resource to get moved to the function parameter (and be destroyed at the end of the function when the function parameters go out of scope). Then when you go to access your auto-ptr argument from the caller, you're suddenly deferencing a null pointer.
2. `std::auto_ptr` always deletes its contents using non-array delete. This means `auto_ptr` won't work correctly with dynamically allocated arrays.
3. `std::auto_ptr` doesn't play nice with a lot of other classes in the standard library, including most of the containers and algorithms.
