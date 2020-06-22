#Rethrowing exceptions
Occasionally you may run into a case where you want to catch an exception, but not want to(or have the ability to) fully handle it at the point where you catch it.This is common when you want to log an error, but pass the issue along to the caller to actually handle.
```cpp
#include <iostream>
    class Base {
public:
    Base() {}
    virtual void print() { std::cout << "Base"; }
};

class Derived : public Base {
public:
    Derived() {}
    virtual void print() { std::cout << "Derived"; }
};

int main() {
    try {
        try {
            throw Derived();
        } catch (Base &b) {
            std::cout << "Caught Base b, which is actually a ";
            b.print();
            std::cout << "\n";
            throw; // note: We're now rethrowing the object here
        }
    } catch (Base &b) {
        std::cout << "Caught Base b, which is actually a ";
        b.print();
        std::cout << "\n";
    }

    return 0;
}
```
