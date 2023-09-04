# Factory Method
Abstract Factory is often implemented with factory methods.
Factory methods are usually called within Template Methods.

The Factory Method is a creational design pattern that provides an interface for creating
objects but allows subclasses to alter the type of objects that will be created.
It promotes loose coupling by abstracting the object creation process and deferring it to
subclasses, which can provide different implementations of the factory method to produce
objects with varying behaviors or properties

```cpp
#include <iostream>
#include <string>

// Abstract Product
class Product {
public:
    virtual void use() const = 0;
};

// Concrete Products
class ConcreteProductA : public Product {
public:
    void use() const override {
        std::cout << "Using Concrete Product A" << std::endl;
    }
};

class ConcreteProductB : public Product {
public:
    void use() const override {
        std::cout << "Using Concrete Product B" << std::endl;
    }
};

// Abstract Factory
class Factory {
public:
    virtual Product* createProduct() const = 0;
};

// Concrete Factories
class ConcreteFactoryA : public Factory {
public:
    Product* createProduct() const override {
        return new ConcreteProductA();
    }
};

class ConcreteFactoryB : public Factory {
public:
    Product* createProduct() const override {
        return new ConcreteProductB();
    }
};

int main() {
    std::unique_ptr<Factory> factoryA = std::make_unique<ConcreteFactoryA>();
    std::unique_ptr<Factory> factoryB = std::make_unique<ConcreteFactoryB>();

    Product* productA = factoryA->createProduct();
    Product* productB = factoryB->createProduct();

    productA->use(); // Output: Using Concrete Product A
    productB->use(); // Output: Using Concrete Product B

    delete productA;
    delete productB;

    return 0;
}
```
