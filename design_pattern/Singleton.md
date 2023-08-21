# Singleton Pattern
Registry of singletons:
```cpp
#include <iostream>
#include <unordered_map>
#include <string>

// Base Singleton
class SingletonBase {
public:
    virtual void commonMethod() {
        std::cout << "Common method called." << std::endl;
    }

private:
    SingletonBase() {}  // Private constructor
    SingletonBase(const SingletonBase&) = delete;  // Disable copy constructor
    void operator=(const SingletonBase&) = delete;  // Disable assignment operator

    friend class SingletonRegistry;
};

// Singleton Instances
class SingletonA : public SingletonBase {
public:
    void specificMethod() {
        std::cout << "Specific method of SingletonA called." << std::endl;
    }
};

class SingletonB : public SingletonBase {
public:
    void specificMethod() {
        std::cout << "Specific method of SingletonB called." << std::endl;
    }
};

// Singleton Registry
class SingletonRegistry {
public:
    static SingletonRegistry& getInstance() {
        static SingletonRegistry instance;
        return instance;
    }

    void registerSingleton(const std::string& key, SingletonBase& singleton) {
        singletons[key] = &singleton;
    }

    SingletonBase* getSingleton(const std::string& key) {
        if (singletons.find(key) != singletons.end()) {
            return singletons[key];
        }
        return nullptr;
    }

private:
    SingletonRegistry() {}  // Private constructor
    SingletonRegistry(const SingletonRegistry&) = delete;  // Disable copy constructor
    void operator=(const SingletonRegistry&) = delete;  // Disable assignment operator

    std::unordered_map<std::string, SingletonBase*> singletons;
};

// Initialize singleton registry and register instances
namespace {
    struct RegisterSingletons {
        RegisterSingletons() {
            SingletonRegistry::getInstance().registerSingleton("SingletonA", SingletonA::getInstance());
            SingletonRegistry::getInstance().registerSingleton("SingletonB", SingletonB::getInstance());
        }
    } registerSingletons;
}

int main() {
    SingletonBase* instanceA = SingletonRegistry::getInstance().getSingleton("SingletonA");
    if (instanceA) {
        instanceA->commonMethod();
        SingletonA* singletonA = dynamic_cast<SingletonA*>(instanceA);
        if (singletonA) {
            singletonA->specificMethod();
        }
    }

    SingletonBase* instanceB = SingletonRegistry::getInstance().getSingleton("SingletonB");
    if (instanceB) {
        instanceB->commonMethod();
        SingletonB* singletonB = dynamic_cast<SingletonB*>(instanceB);
        if (singletonB) {
            singletonB->specificMethod();
        }
    }

    return 0;
}

```
