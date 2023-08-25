# Adapter
Also known as Wrapper;
Sometimes a toolkit class that's designed for reuse isn't reusable only because it's
interface doesn't match the domain-specific interface an application requires.

A class adapter uses multiple inheritance to adapt interfaces.
However, keep in mind that using multiple inheritance can introduce complexities, and you
should carefully manage potential conflicts between the base classes.
```cpp
#include <iostream>

// Adaptee class with an incompatible interface
class Adaptee {
public:
    void specificRequest() {
        std::cout << "Adaptee's specific request." << std::endl;
    }
};

// Target interface expected by the client
class Target {
public:
    virtual void request() = 0;
};

// Adapter class that inherits from Adaptee and implements the Target interface
class Adapter : public Adaptee, public Target {
public:
    void request() override {
        specificRequest();
    }
};

int main() {
    // Create an adapter instance
    Adapter adapter;

    // Client code works with the adapter using the Target interface
    Target* target = &adapter;
    target->request();

    return 0;
}

```
The object adapter uses object composition to combine classes with different interfaces.
```cpp
// Legacy class with incompatible interface
class LegacyRectangle {
public:
    LegacyRectangle(double width, double height) : width(width), height(height) {}

    double calculateArea() {
        return width * height;
    }

private:
    double width;
    double height;
};

// Target interface expected by the client
class Shape {
public:
    virtual double computeArea() = 0;
};

// Adapter class that adapts LegacyRectangle to the Shape interface
class RectangleAdapter : public Shape {
public:
    RectangleAdapter(LegacyRectangle* rectangle) : rectangle(rectangle) {}

    double computeArea() override {
        return rectangle->calculateArea();
    }

private:
    LegacyRectangle* rectangle;
};

int main() {
    // Existing LegacyRectangle instance
    LegacyRectangle legacyRectangle(5.0, 10.0);

    // Create an adapter instance
    RectangleAdapter adapter(&legacyRectangle);

    // Client code works with the adapter using the target interface
    Shape* shape = &adapter;
    double area = shape->computeArea();
    std::cout << "Area: " << area << std::endl;

    return 0;
}

```
