#Exceptions, functions, and stack unwinding
####Throwing exceptions outside of a try block
```cpp
// A modular square root function
double mySqrt(double x) {
    // If the user entered a negative number, this is an error condition
    if (x < 0.0)
        throw "Can not take sqrt of negative number"; // throw exception of type const char*
    return sqrt(x);
}

int main() {
    std::cout << "Enter a number: ";
    double x;
    std::cin >> x;

    try { // Look for exceptions that occur within try block and route to attached catch block(s)
        double d = mySqrt(x);
        std::cout << "The sqrt of " << x << " is " << d << '\n';
    } catch (const char* exception) { // catch exceptions of type const char*
        std::cerr << "Error: " << exception << std::endl;
    }
    return 0;
}
```
First, the program looks to see if the exception can be handled immediately (which means it was thrown inside a try block).
If not, the current function is terminated, and the program checks to see if the function’s caller will handle the exception.
If not, it terminates the caller and checks the caller’s caller.
Each function is terminated in sequence until a handler for the exception is found, or until main() is terminated without the exception being handled.
This process is called **unwinding the stack** (see the lesson on the stack and the heap if you need a refresher on what the call stack is).
