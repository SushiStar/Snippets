# Composite
Compose objects into tree structures to represent part-whole hierarchies. Composite lets
client treat individual objects and compositions of objects uniformly.
The Composite pattern describes how to use recursive composition so that clients don't
have to make this distinction.

The key to a composite pattern is an abstract class that represents both primitives and
their containers.

```cpp
#include <iostream>
#include <vector>

// Component interface
class Graphic {
public:
    virtual void draw() = 0;
};

// Leaf class representing a simple shape
class SimpleShape : public Graphic {
public:
    void draw() override {
        std::cout << "Drawing a simple shape." << std::endl;
    }
};

// Composite class representing a group of graphics
class CompositeGraphic : public Graphic {
public:
    void draw() override {
        std::cout << "Drawing a composite graphic:" << std::endl;
        for (auto graphic : graphics) {
            graphic->draw();
        }
    }

    void add(Graphic* graphic) {
        graphics.push_back(graphic);
    }

private:
    std::vector<Graphic*> graphics;
};

int main() {
    // Create simple shapes
    SimpleShape shape1, shape2;

    // Create a composite graphic
    CompositeGraphic composite;

    // Add shapes to the composite
    composite.add(&shape1);
    composite.add(&shape2);

    // Draw individual shapes and the composite
    shape1.draw();
    shape2.draw();

    std::cout << "\nDrawing the composite graphic:" << std::endl;
    composite.draw();

    return 0;
}

```
