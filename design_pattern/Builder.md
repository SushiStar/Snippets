# Builder

```cpp
#include <iostream>
#include <string>

class Product {
public:
    void setPart1(const std::string& part) {
        part1 = part;
    }

    void setPart2(const std::string& part) {
        part2 = part;
    }

    void show() const {
        std::cout << "Part 1: " << part1 << "\n";
        std::cout << "Part 2: " << part2 << "\n";
    }

private:
    std::string part1;
    std::string part2;
};

class Builder {
public:
    virtual void buildPart1(){};
    virtual void buildPart2(){};
    virtual Product getProduct(){};
};

class ConcreteBuilder : public Builder {
public:
    void buildPart1() override {
        product.setPart1("Concrete Part 1");
    }

    void buildPart2() override {
        product.setPart2("Concrete Part 2");
    }

    Product getProduct() override {
        return product;
    }

private:
    Product product;
};

class Director {
public:
    void setBuilder(Builder* builder) {
        this->builder = builder;
    }

    void construct() {
        builder->buildPart1();
        builder->buildPart2();
    }

private:
    Builder* builder;
};

int main() {
    ConcreteBuilder concreteBuilder;
    Director director;

    director.setBuilder(&concreteBuilder);
    director.construct();

    Product product = concreteBuilder.getProduct();
    product.show();

    return 0;
}
```
