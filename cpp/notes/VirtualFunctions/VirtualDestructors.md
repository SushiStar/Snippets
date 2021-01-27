# Virtual destructors, virtual assignments, and overriding virtualization
### Virtual destructors
You should always make your destructors virtual if you're dealing with inheritance.
Base is a pointer, when base is deleted, the program looks to see if the Base destructor is virtual. If it's not, so it assumes it only needs to call the Base destructor.
However, we really want the delete function to call Derived's destructor (which will call Base's destructor in turn), otherwise allocated memory will not be deleted. We do this by making Base's destructor virtual:

```cpp
class Base {
public:
    virtual ~Base() { // note: virtual
        std::cout << "Calling ~Base()\n";
    }
};

class Derived: public Base {
private:
    int* m_array;
public:
    Derived(int length) {
        m_array = new int[length];
    }

    virtual ~Derived() { 	// note: virtual
        std::cout << "Calling ~Derived()\n";
        delete[] m_array;
    }
};
```
>Rule
>Whenever you are dealing with inheritance, you should make any explicit destructors virtual.

As with normal virtual member functions, if a base class function is virtual, all derived overrides will be considered virtual regardless of whether they are specified as such. It is not necessary to create an empty derived class destructor just to mark it as virtual.

### Ignoring virtualization
There may be cases where you want a Base pointer to a Derived object to call `Base::getName()` instead of `Derived::getName()`. To do so , simply use the scope resolution operator.

* If you intend your class to be inherited from, make sure your desturctor is virtual.
* If you do not intend your class to be inherited from, mark your class as final. This will prevent other classes from inheriting from it in the first place, without imposing any other use restrictions on the class itself.
