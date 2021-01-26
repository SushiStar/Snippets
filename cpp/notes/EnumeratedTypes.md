# Enumerated types
An enumerated type (also called an **enumeration** or **enum**) is a data type where every possible value is defined as a symbolic constant (called an **enumerator**). Enumerations are defined via the **enum** keyword.
```cpp
// Define a new enumeration named Color
enum Color
{
    // Here are the enumerators
    // These define all the possible values this type can hold
    // Each enumerator is separated by a comma, not a semicolon
    COLOR_BLACK,
    COLOR_RED,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_WHITE,
    COLOR_CYAN,
    COLOR_YELLOW,
    COLOR_MAGENTA, // see note about trailing comma on the last enumerator below
}; // however the enum itself must end with a semicolon

// Define a few variables of enumerated type Color
Color paint = COLOR_WHITE;
Color house(COLOR_BLUE);
Color apple { COLOR_RED };
```
Defining an enumeration (or any user-defined data type) does allocate any memory. When a variable of the enumerated type is defined (such as variable paint in the example above), memory is allocated for that variable at that time.
Note that each enumerator is separated by a comma, and the entire enumeration is ended with a semicolon.

### Naming enumerations and enumerators
Providing a name for an enumeration is optional, but common. Enums without a name are sometimes called anonymous enums. Enumeration names are often named starting with a capital letter.
Enumerators must be given names, and are typically named either using all caps (e.g. COLOR\_WHITE), or prefixed with a k and intercapped (e.g. kColorWhite).

### Enumerator scope
Because enumerators are placed into the same namespace as the enumeration, an enumerator name can't be used in multiple enumerations within the same namespace:

### Enumerator values
Each enumerator is automaticall assigned an integer value based on its position in the enumeration list. By default, the first enumerator is assigned the integer value 0, and each subsequent enumerator has a value one greater than the previous enumerator.
It is possible to explicitly define the value of enumerator. These integer values can be positive or negative and can share the same value as otehr enumerators. Any non-defined enumerators are given a value one greater than the previous enumerator.
```cpp
// define a new enum named Animal
enum Animal
{
    ANIMAL_CAT = -3,
    ANIMAL_DOG, // assigned -2
    ANIMAL_PIG, // assigned -1
    ANIMAL_HORSE = 5,
    ANIMAL_GIRAFFE = 5, // shares same value as ANIMAL_HORSE
    ANIMAL_CHICKEN // assigned 6
};
```
Note in this case, ANIMAL\_HORSE and ANIMAL\_GIRAFFE have been given the same value. When this happens, the enumerations become non-distinct -- essentially, ANIMAL\_HORSE and ANIMAL\_GIRAFFE are interchangeable.
>**Best practice**
> Don't assign specific values to your enumerators.
>**Rule**
>Don't assign the same value to two enumerators in the same enumeration unless there's a very good reason.

Because enumerated values evaluate to integers, they can be assigned to integer variables. The compiler will *not* implicitly convert an integer to an enumerated value. The following will produce a compiler error:
```cpp
Animal animal = 5; // will cause compiler error
```
However, you can force it to do so via static\_cast:
```cpp
Color color = static_cast<Color>(5);    // ugly
```
If you want to use a different integer type for enumerators, for example to save bandwidth when networking an enumerator, you can specify it at the enum declaration.
```cpp
// Use an 8 bit unsigned integer as the enum base.
enum Color : std::unint_least8_t
{
    COLOR_BLACK,
    COLOR_RED,
    // ...
};
```
Since enumerators aren't usually used for arithmetic or comparisions, it's safe to use an unsigned integer. We also need to specify the enum base when we want to forward declare an enum.
```cpp
enum Color; // Error
enum Color : int; // Okay

// ...

// Because Color was forward declared with a fixed base, we
// need to specify the base again at the definition.
enum Color : int
{
    COLOR_BLACK,
    COLOR_RED,
    // ...
};
```
As with constant variables, enumerated types show up in the debugger, making them more useful than #defined values in this regard.

## Enum classes
C++11 defines a new concept, the **enum class** (also called a scoped enumeration), which makes enumerations both strongly typed and strongly scoped. To make an enum class, we use the keyword **class** after the enum keyword.
With normal enumerations, enumerators are placed in the same scope as teh enmeration itself, so you can typically access enumerators directly. However, with enum classes, the strong scoping rules mean that all enumerators are considered part of the enumeration, so you have to use a scope qualifier to access the enumerator. The help keeps name pollution and the potential for name conflicts down.
