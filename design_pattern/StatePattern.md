# State Pattern
It allows an object to alter its behavior when its internal state changes.
Use the state pattern in the following cases:
* An object's behavior depends on its state, and it must change its behavior at run-time
  depending on that state.
* Operations have large, multipart conditional statements that depend on the object's
  state.
The state class is a state, but it shouldn't contain any member variables, or the state
itself shouldn't have a state.

```cpp
#include <iostream>

// Context class representing the vending machine
class VendingMachine;

// State interface
class State {
public:
    virtual void insertMoney(VendingMachine& machine, int amount) = 0;
    virtual void selectProduct(VendingMachine& machine, int productId) = 0;
    virtual void dispenseProduct(VendingMachine& machine) = 0;
};

// Concrete state classes
class NoProductState : public State {
public:
    void insertMoney(VendingMachine& machine, int amount) override {
        std::cout << "No products available." << std::endl;
    }

    void selectProduct(VendingMachine& machine, int productId) override {
        std::cout << "No products available." << std::endl;
    }

    void dispenseProduct(VendingMachine& machine) override {
        std::cout << "No products available." << std::endl;
    }
};

class HasProductState : public State {
public:
    void insertMoney(VendingMachine& machine, int amount) override {
        machine.addMoney(amount);
        std::cout << "Money added: " << amount << std::endl;
    }

    void selectProduct(VendingMachine& machine, int productId) override {
        machine.setSelectedProduct(productId);
        std::cout << "Product selected: " << productId << std::endl;
    }

    void dispenseProduct(VendingMachine& machine) override {
        machine.dispenseSelectedProduct();
        machine.changeState(new NoProductState());
    }
};

class VendingMachine {
public:
    VendingMachine() : state(new NoProductState()) {}

    void addMoney(int amount) {
        state->insertMoney(*this, amount);
    }

    void selectProduct(int productId) {
        state->selectProduct(*this, productId);
    }

    void dispenseSelectedProduct() {
        state->dispenseProduct(*this);
    }

    void changeState(State* newState) {
        delete state;
        state = newState;
    }

private:
    State* state;
};

int main() {
    VendingMachine vendingMachine;

    vendingMachine.addMoney(5);
    vendingMachine.selectProduct(1);
    vendingMachine.dispenseSelectedProduct();

    return 0;
}
```
