# Chapter10: Expressions

C++ provides assignment operators for the binary operators:
```
+ - * / % & | ^ << >>

// so that the following assignment operators are possible:
+=  -=  *=  /=  %=  &=  |=  ^=  <<=  >>=
```
By default, operator **>>** skips whitespace (that is, spaces, tabs, newlines, etc.).

The stream **cerr** is an unbuffered output stream usually used to report errors.
The name of the program ( as it occurs on the command line) is passed as argv[0], so argc is always at least 1. The list of arguments is zero-terminated; that is, argv[argc] == 0.

**argc** and **argv** are still a source of minor, yet annoying, bugs. To avoid those and especially to make it easier to pass around the program arguments, I tend to use a simple function to create a <code>std::vector<string></code>
```
std::vector<string> arguments (int argc, char* argv[]) {
    std::vector<string> res;
    for (int i = 0; i!=argc; ++i) res.push_back(argv[i]);
    return res;
}
```
Ther operators ,(comma), &&(logical and), and ||(logical or) guarantee that their left-hand operand is evaluated before their right-hand operand. (***short circuit evaluation***)
Parenthesse should be used whenever a programmer is in doubt about those rules.

###**Constant**
C++ offers two related meanings of "constant":
* constexpr: Evaluate at compile time;
* cosnt: Do not modify in this scope;

The main idea is performance improvement of programs by doing computations at compile time rather than run time. Note that once a program is compiled and finalized be developer, it is run multiple times by users. The idea is to spend time in compilation and save time at run time (similar to template metaprogramming).
Rules:

<ul>
<li>In C++ 11, a constexpr function should contain only one return statement. C++ 14 allows more than one statements.</li>
<li>constexpr function should refer only constant global variables.</li>
<li>constexpr function can call only other constexpr function not simple function.</li>
<li>Function should not be of void type and some operator like prefix increment (++v) are not allowed in constexpr function.</li>
</ul>
#####**constexpr vs inline functions**:
Both are for performance improvements, inline functions are request to compiler to expand at compile time and save time of function call overheads. In inline functions, expressions are always evaluated at run time. constexpr is different, here expressions are evaluated at compile time.

We can use **constexpr** functions and literal types to provide a significant level of type safety and expressive power.
A class with **constexpr** constructor is called a **literal** type.


###**Implicit Type Conversion**
* Promotions: The implicit conversions that preserve values are commonly referred to as ***promotions***.
* Conversions: Be careful about nawworing conversions, the {}-initializer syntax prevents narrowing. If potentially narrowing conversions are unavoidable, considering using some form of run-time checked conversion function, such as <code>narrow\_cast<>()</code>.
* Any pointer to an object type can be implicitly converted to a <code>void\*</code>. A pointer to a derived class can be implicitly converted to a pointer (reference) to an accessible and unambiguous base.
* A pointer to a function or to a member cannot be implicitly converted to a <code>void\*</code>.
* Conversion from an floating-point type to an integer type truncates.  
