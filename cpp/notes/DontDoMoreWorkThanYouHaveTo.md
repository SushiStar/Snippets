# Don't Do More Work Than You Have To

### Container Practices
* Always prefer `std::array`
* Then `std::vector`
* Then only differ if you need specific behavior
* Make sure you understand what the library has to do

***Always `const`***
```cpp
int main() {
    const std::string s = "A somewhat rather long string";
}
```
* Construct and initialize in one step
* ~32% more efficient

### Always `const` - Complex Initialization - Use IIFE
 ```cpp
int main() {
  const int i = std::rand();
  std::string s;
  switch (i % 4) {
    case 0:
      s = "long string is mod 0";
      break;
    case 1:
      s = "long string is mod 1";
      break;
    case 2:
      s = "long string is mod 2";
      break;
    case 3:
      s = "long string is mod 3";
      break;
  }
}

int main()
{
  const int i = std::rand();
  const std::string s = [&](){
    switch (i % 4) {
      case 0:
        return "long string is mod 0";
      case 1:
        return "long string is mod 1";
      case 2:
        return "long string is mod 2";
      case 3:
        return "long string is mod 3";
    }
  }();
}
```
~31% more efficient

### Don't Recalculate Values - Calculate on First Use
```cpp
struct Int {
    Int(std::string t_s) : s(std::move(t_s)) {}
    int val () const {
        if (!is_calculated) {
            value = std::atoi(s);
            is_calculated = true;
        }
        return value;
    }
    mutable std::atomic_bool is_calculated = false;
    mutable std::atomic_int value
};
```
* Branching is slower
* Atomics are slower
```cpp
struct Int
{
  Int(const std::string &t_s) : m_i(std::atoi(t_s.c_str())) {}

  int val() const {
    return m_i;
  }
  int m_i;
};
```
* No branching, no atomics, smaller runtime (int vs string)
* In the context of a large codebase, this took ~2 years to find
* Resulted in 10% performance across the system
* The simpler solution is always the best solution

### Don't Disable Move Operations / Use Rule of 0
```cpp
struct Base {
  virtual ~Base() = default;
  virtual void do_a_thing() = 0;
};

struct Derived : Base {
  virtual ~Derived() = default;
  void do_a_thing() override {}
};

struct Base {
  virtual ~Base() = default;
  Base() = default;
  Base(const Base &) = default; Base& operator=(const Base&) = default;
  Base(Base &&) = default; Base& operator=(Base &&) = default;

  virtual void do_a_thing() = 0;
};

struct Derived : Base {
  virtual void do_a_thing() {}
};
```
* 10% improvement with fixing this in just one commonly used class

### Avoid Named Temporaries
```cpp
#include <string>

struct S {
  S(std::string t_s) : s(std::move(t_s)) {}
  std::string s;
};

int main()
{
  for (int i = 0; i < 10000000; ++i) {
    std::string s = std::string("a not very short string") + "b";
    S o(std::move(s));
  }
}

struct S {
  S(std::string t_s) : s(std::move(t_s)) {}
  std::string s;
};

int main()
{
  for (int i = 0; i < 10000000; ++i) {
    S o(std::string("a not very short string") + "b");
  }
}
```
* 2% efficient again
* Can lead to less readable code sometimes, but more maintainable than `std::move` calls
* This is taking the "don't declare a variable until you need it" philosophy to its
  ultimate conclusion.

# Smaller Code is Faster Code
### Never Ever Ever Use `std::bind`
```cpp
std::string add(const std::string &lhs, const std::string &rhs) {
  return lhs + rhs;
}

int main() {
  const auto f = std::bind(add, "Hello ", std::placeholders::_1);
  f("World");
}
```
* 1.9X slower than the bare function call
* ~15% compile time overhead
* Effective Modern C++ #34

### Use Lambdas
```cpp
std::string add(const std::string &lhs, const std::string &rhs) {
  return lhs + rhs;
}

int main() {
  const auto f = [](const std::string &b) {
    return add("Hello ", b);
  };
  f("World");
}
```
* 0 overhead compared to direct function call
* 0% compile time overhead

### Don't Repeat Yourself in Templates
