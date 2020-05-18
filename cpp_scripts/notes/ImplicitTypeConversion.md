#Type conversion
The process of converting a value from one data type to another is called **type conversion**. `Type conversion` can happen in many different cases:
    * When assigning to or initializing a variable with a value of a different data type.
    * When passing a value to a function where the function parameter is of a different data type.
    * When returning a value from a function where the function return type is of a different type.
    * Using a binary operator with operands of different types.

### Implicit type conversion
**Implicit type conversion** (also called **automatic type conversion** or **coercion**) is performed whenever one data type is expected, but a different data type is supplied.
There are basic types of `implicit type conversion: promotions` and `conversions`.
####Numeric promotion
Whenever a value from one fundamental data type is converted into a value of a larger fundamental data type from the same family, this is called a **numeric promotion** (or **widening**, though this term is usually reserved for integers).
    * Integral promotion involves the conversion of integer types narrower than int (which includes `bool`, `char`, `unsigned char`, `signed char`, `unsigned short`, and `signed short`) to an `int` (if possible) or an `unsigned int`.
    * Floating point promotion involves the conversion of a `float` to a `double`
> Under the hood, promotions generally involve extending the binary representations of a number.
####Numeric conversions
When we convert a value from a larger type to a similar type, or between different types, this is called a **numeric conversion**.
In *all* casses, converting a value into a type that doesn't have a large enough range to support the value will lead to unexpected results.

### Explicit type conversion (casting) and static\_cast
A **cast** represents an request by the programmer to do an `explicit type conversion`.
####Type casting
In C++, there are 5 different types of casts: `c-style, casts, static casts, const casts, dynamic casts,` and `reinterpret casts`. The latter four are sometimes referred to as **named casts**.
`Const casts` and `reinterpret casts` should generally be avoided because they are only useful in rare cases and can be harmful if used incorrectly.
**C-style casts** are done via the () operator, with the name of the type to convert the value to placed inside the parenthesis.
```cpp
float f {(float)i1/i2};
```
C++ will let you use a `C-style cast` with a more function-call like syntax:
```cpp
float f {float(i1)/i2)};
```
Although a `C-style cast` appears to be a single cast, it can actually perform a variety of different conversions depending on context. Thin can include a `static cast`, a `const cast` or a `reinterpret cast`. As a result, `C-style casts` are at risk for being inadvertently misused, and not producing the expected behavior, something is easily avoidable by using the C++ casts instead. 

####static\_cast
C++ introduces a casting operator called static\_cast, which can be used to convert a value of one type to a value of another type. The `static\_cast` operator takes a single value as input, and outputs the same value converted to the type specified inside the angled brackets. `Static\_cast` is best used to convert one fundamental type into anohter. 
The main advantage of `static\_cast` is that it provides compile-time type checking, making it harder to make an inadvertent error.
> Favor static\_cast when you need to convert a value from one type to another type.
###Using casts to make implicit type conversions clear
