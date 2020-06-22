#Basic exception handling
Exceptions in C++ are implemented using three keywords that work in conjunction with each other: throw, try, and catch.

####Throw exceptions
We use signals all time in real life to note that particular events have occurred.
In C++ **throw statement** is used to signal that an exception or error case has occurred. Signaling that an exception has occurred is also commonly called **raising** an exception.
To use a throw statement, simply use the throw keyword, followed by a value of any data type you wish to use to signal that an error has occurred.
```cpp
throw -1; // throw a literal integer value
throw ENUM_INVALID_INDEX; // throw an enum value
throw "Can not take square root of negative number"; // throw a literal C-style (const char*) string
throw dX; // throw a double variable that was previously defined
throw MyException("Fatal Error"); // Throw an object of class MyException
```

####Looking for exceptions
In C++, we use the **try** keyword to define a block of statements (called a try block). The try block acts as an observer, looking for any exceptions that are thrown by any of the statements within the try block.
####Handling exceptions
Actually handling exceptions is the job of the **catch** block(s). The **catch** keyword is used to define a block of code (called a catch block) that handles exceptions for a single data type.
```cpp
catch (int x) {
    // Handle an exception of type int here
    std::cerr << "We caught an int exception with value" << x << '\n';
}
```
Try blocks and catch blocks work together -- A try block detects any exceptions that are thrown by statements within the try block, and routes them to the appropriate catch block for handling. A try block must have at least one catch block immediately following it, but may have multiple catch blocks listed in sequence.
Catch parameters work just like function parameters, with the parameter being available within the subsequent catch block. Exceptions of fundamental types can be caught by value, but exceptions of non-fundamental types should be caught by const reference to avoid making an unnecessary copy.
Just like with functions, if the parameter is not going to be used in the catch block, the variable name can be omitted.

####Putting throw, try and catch together
```cpp
int main() {
    try {

        // Statements that may throw exceptions you want to handle go here
        throw -1; // here's a trivial example

    } catch (int x) {

        // Any exceptions of type int thrown within the above try block get sent here
        std::cerr << "We caught an int exception with value: " << x << '\n';

    } catch (double) { 		// no variable name since we don't use the exception itself in the catch block below

        // Any exceptions of type double thrown within the above try block get sent here
        std::cerr << "We caught an exception of type double" << '\n';

    } catch (const std::string &str) { // catch classes by const reference

        // Any exceptions of type std::string thrown within the above try block get sent here
        std::cerr << "We caught an exception of type std::string" << '\n';
    }
    std::cout << "Continuing on our merry way\n";
    return 0;
}
```

When an exception is raised (using throw), execution of the program immediately jumps to the nearest enclosing try block (propagating up the stack if necessary to find an enclosing try block -- we’ll discuss this in more detail next lesson). If any of the catch handlers attached to the try block handle that type of exception, that handler is executed and the exception is considered handled.

If no appropriate catch handlers exist, execution of the program propagates to the next enclosing try block. If no appropriate catch handlers can be found before the end of the program, the program will fail with an exception error.

Note that the **compiler will not perform implicit conversions or promotions when matching exceptions with catch blocks!** For example, a char exception will not match with an int catch block. An int exception will not match a float catch block. **However, casts from a derived class to one of its parent classes will be performed.**

####What catch blocks typically do
First, catch blocks may print an error (either to the console, or a log file).

Second, catch blocks may return a value or error code back to the caller.

Third, a catch block may throw another exception. Because the catch block is outside of the try block, the newly thrown exception in this case is not handled by the preceding try block -- it’s handled by the next enclosing try block.
