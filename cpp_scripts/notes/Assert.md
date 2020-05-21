#Assert and static_assert
An assert statement is a preprocessor macro that evaluates a condition expression at runtime. If the conditional expression is true, the assert statement does nothing. If the conditional expression evaluates to be false, an error message is displayed and the program is terminated.
###Making your assert statements more descriptive
Simply add a C-style string description jointed with a logical AND:
```cpp
assert (found && "Car could not be foudn in database");
```
###NDEBUG and other considerations
The `assert()` functions comes with a small performance cost that is incurred each time the assert condition is checked. Furthermore, asserts should never be encountered in production code. Consequently, many developers prefer that asserts are only active in debug builds. C++ comes with a way to turn off asserts in production code: `#define NDEBUG`.
```cpp
#define NDEBUG
// all assert() calls will now be ignored to the end of the file
```
###static\_assert
`static_assert` is designed to operate at compile time, causing the compiler to error out if the condition is not true.
```cpp
static_assert(sizeof(long) == 8, "long must be 8 bytes");
static_assert(sizeof(int) == 4, "int must be 4 bytes");
int main() {
    return 0; 
}
```
Because `static_assert` is evaluated by the compiler, the condition part of a `static_assert` must be able to be evaluated at compile time.
