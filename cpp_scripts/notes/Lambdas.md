#Introduction to lambdas (anonymous functions)
A lambda expression (also called **lambda** or **closure**) allows us to define an anonymous function inside another function. The nesting is important, as it follows us both to avoid namespace naming pollution, and to define the functions as close to where it is used as possible (providing additional context).
The syntax for lambdas is one of the  weirder things in C++:
```cpp
[captureClause] (parameters) -> returnType {
    statements;
}
```
The `captureClause` and `parameters` can both be empty if they are not needed.
The `return type` is optional, and if omitted, `auto` will be assumed (thus using type interface used to determine the return type).
Also note that lambdas have no name, so we don't need to provide one.
```cpp
This means a trivial lambda definition looks like this:
#include <iostream>
int main() {
    []() {};    // defines a lambda with no captures, no parameters, and no return type
    return 0;
}
```
Another example:
```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>
int main() {
    std::arary<std::string_view, 4> arr{"apple", "banana", "walnut", "lemon"};

    // Define the function right where we use it.
    auto found {std::find_if (arr.begin(), arr.end(), [](std::string_view str) {
        return (str.find("nut") != std::string_view::npos);
        })};
    if (found == arr.end()) {
        std::cout << "No nuts \n";
    } else {
        std::cout << "Found" << *found << '\n';
    }
    return 0;
}
```
#Type of lambda
The use of lambda is sometimes called a function literal. A named lambda along with a good function name can make code easier to read.
```cpp
// Bad: We have to read the lambda to understand what's happening.
return std::all_of(array.begin(), array.end(), [](int i){ return ((i % 2) == 0); });

// Good: Instead, we can store the lambda in a named variable and pass it to the function.
auto isEven{
  [](int i)
  {
    return ((i % 2) == 0);
  }
};

return std::all_of(array.begin(), array.end(), isEven);
```
As it turns out, lambdas don't have a type that we can explicitly use. When we write a lambda, the compiler generates a unique type just for the lambda that is not exposed to us. In actuality, lambdas aren't funtions. They are a special kind of object called a functor. Functors are objects that contain an overloaded `opeator()` that make them callable like a function.
```cpp
int main()
{
  // A regular function pointer. Only works with with an empty capture clause.
  double (*addNumbers1)(double, double){
    [](double a, double b) {
      return (a + b);
    }
  };

  addNumbers1(1, 2);

  // Using std::function. The lambda could have a non-empty capture clause (Next lesson).
  std::function addNumbers2{ // note: pre-C++17, use std::function<double(double, double)> instead
    [](double a, double b) {
      return (a + b);
    }
  };

  addNumbers2(3, 4);

  // Using auto. Stores the lambda with its real type.
  auto addNumbers3{
    [](double a, double b) {
      return (a + b);
    }
  };

  addNumbers3(5, 6);

  return 0;
```

##Lambda captures
Unlike nested blocks, where any identifier defined in an outer block is accessible in the scope of the nested block, lambdas can only access specific kinds of identifiers: global identifiers, entities that are known at compile time, and entities with static storage duration.
###The capture clause
The **capture clause** is used to (indirectly) give a lambda access to variables available in the surrounding scope that it normally would not have access to. All we ned to do is list the entities we want to access from within the lambda as part of the capture clause.
```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>
#include <string>

int main()
{
  std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

  std::cout << "search for: ";

  std::string search{};
  std::cin >> search;

  // Capture @search                                vvvvvv
  auto found{ std::find_if(arr.begin(), arr.end(), [search](std::string_view str) {
    return (str.find(search) != std::string_view::npos);
  }) };

  if (found == arr.end())
  {
    std::cout << "Not found\n";
  }
  else
  {
    std::cout << "Found " << *found << '\n';
  }

  return 0;
}
```
###So how do captures actually work?
When a lambda definition is executed, for each variable that the lambda captures, a clone of that variable is made (with an identical name) inside the lambda. These cloned variables are initialized from the outer scope variables of the same name at this point.
While these cloned variable have the same name, they don't necessarily have the same type as the original variable.
>**Key insight**
>The captured variables of a lambda are clones of the outer scope variables, not the actual variables.
> When the compiler encounters a lambda definition, it creates a custom object definition for the lambda. Each captured variable becomes a data member of the object.
>At runtime, when the lambda definition is encountered, the lambda object is instantiated, and the members of teh lambda are initizlied at that point.
###Capture default to const value
By default, varialbes are captured by `const value`. This means when the lambda is created, the lambda captures a constant copy of the outer scope variable, which means that the lambda is not allowed to modify them.
```cpp
#include <iostream>

int main()
{
  int ammo{ 10 };

  // Define a lambda and store it in a variable called "shoot".
  auto shoot{
    [ammo]() {
      // Illegal, ammo was captured as a const copy.
      --ammo;

      std::cout << "Pew! " << ammo << " shot(s) left.\n";
    }
  };

  // Call the lambda
  shoot();

  std::cout << ammo << " shot(s) left\n";

  return 0;
}
```
###Mutable capture by value
To allow modifications of variables that were captured by the value, we can mark the lambda as `mutable`. The **mutalbe** keyword in this context removes the `const` qualification from *all* variables captured by value.
```cpp
#include <iostream>

int main()
{
  int ammo{ 10 };

  auto shoot{
    // Added mutable after the parameter list.
    [ammo]() mutable {
      // We're allowed to modify ammo now
      --ammo;

      std::cout << "Pew! " << ammo << " shot(s) left.\n";
    }
  };

  shoot();
  shoot();

  std::cout << ammo << " shot(s) left\n";

  return 0;
}
```
###Capture by reference
We can also capture variables by reference to allow our lambda to affect the value of the argument.
To capture a variable by reference, we prepend an ampersand (`&`) to the variable name. Variables that are captured by reference are non-const, unless the variable they're capturing is `const`.
```cpp
#include <iostream>

int main()
{
  int ammo{ 10 };

  auto shoot{
    // We don't need mutable anymore
    [&ammo]() { // &ammo means ammo is captured by reference
      // Changes to ammo will affect main's ammo
      --ammo;

      std::cout << "Pew! " << ammo << " shot(s) left.\n";
    }
  };

  shoot();

  std::cout << ammo << " shot(s) left\n";

  return 0;
}
```
Capturing multiple variables
Multiple variables can be captured by separating them with a comma. This can include a mix of variables captured by value or by reference:
```cpp
int health{ 33 };
int armor{ 100 };
std::vector<CEnemy> enemies{};

// Capture health and armor by value, and enemies by reference.
[health, armor, &enemies](){};
```
###Default captures
A **Default capture** (also called a **capture-default**) captures all variables that are mentioned in the lambda. Variables not mentioned in the lambda are not captured if a default capture is used.
To capture all used variables by value, use a capture value of `=`.
To capture all used variabled by reference, use a capture value of `&`.
Default captures can be mixed with normal captures. We can capture some variables by value and others by reference, but each variable can only be captured once.
```cpp
int health{ 33 };
int armor{ 100 };
std::vector<CEnemy> enemies{};

// Capture health and armor by value, and enemies by reference.
[health, armor, &enemies](){};

// Capture enemies by reference and everything else by value.
[=, &enemies](){};

// Capture armor by value and everything else by reference.
[&, armor](){};

// Illegal, we already said we want to capture everything by reference.
[&, &armor](){};

// Illegal, we already said we want to capture everything by value.
[=, armor](){};

// Illegal, armor appears twice.
[armor, &health, &armor](){};

// Illegal, the default capture has to be the first element in the capture group.
[armor, &](){};
```
###Defining new variables in the lambda-capture
Sometimes we want to capture a variable with a slight modification or declare a new variable that is only visible in the scope of the lambda. We can do so by defining a variable in the lambda-capture without specifying its type.
```cpp
#include <array>
#include <iostream>

int main()
{
  std::array areas{ 100, 25, 121, 40, 56 };

  int width{};
  int height{};

  std::cout << "Enter width and height: ";
  std::cin >> width >> height;

  // We store areas, but the user entered width and height.
  // We need to calculate the area before we can search for it.
  auto found{ std::find_if(areas.begin(), areas.end(),
                           // Declare a new variable that's visible only to the lambda.
                           // The type of userArea is automatically deduced to int.
                           [userArea{ width * height }](int knownArea) {
                             return (userArea == knownArea);
                           }) };

  if (found == areas.end())
  {
    std::cout << "I don't know this area :(\n";
  }
  else
  {
    std::cout << "Area found :)\n";
  }

  return 0;
}
```
`useArea` will only be calculated once when the lambda is defined. The calculated area is stored in the lambda object and is the same for every call. If a lambda is mutable and modifies a variable that was defined in the capture, the original value will be overridden.
>**Best practice**
>Only initialize variables in the capture if their value is short and their type is obvious. Otherwise it's best to define the variable outside of the lambda and capture it.
###Dangling captured variables
If a variable captuerd by reference dies before teh lambda, the lambda will be left holding a dangling reference.
To prevent copies of our lambda from being made in the first place, we can call `std::ref` which allows us to pass a normal type as if it were a reference. By wrapping our lambda in a `std::ref`, whenever anybody tries to make a copy of our lambda, they'll make a copy of the reference instead, which will copy the reference rather than the actual object.
```cpp
#include <iostream>
#include <functional>

void invoke(const std::function<void(void)> &fn)
{
    fn();
}

int main()
{
    int i{ 0 };

    // Increments and prints its local copy of @i.
    auto count{ [i]() mutable {
      std::cout << ++i << '\n';
    } };

    // std::ref(count) ensures count is treated like a reference
    // thus, anything that tries to copy count will actually copy the reference
    // ensuring that only one count exists
    invoke(std::ref(count));
    invoke(std::ref(count));
    invoke(std::ref(count));

    return 0;
}
```
>**Rule**
>Standard library functions may copy function objects (reminder: lambdas are function objects). If you want to provide lambda with mutable captured variables, pass them by reference using std::ref.
>**Best practice**
>Try to avoid lambdas with states altogether. Stateless lambdas are easier to understand and don't suffer from the avove issues, as well as more dangerous issues that arise when you add parallel executions.
