#Chapter 13: Error Handling
The discussions of exceptions focuses on problems that needed to be handled in long-running systems, systems with stringent reliablity requirements, and libraries.
## Exceptions
Example:
```
void taskmster() {
    try{
        auto result = do_task();
        // use result;
    } catch (some error) {
        // failuer to do task: handle the problem.
    }
}
int do_task() {
    if(/* could perform the task */) {
        return result;
    } else {
        throw some_error{};
    }
}
```
The exception-handling mechanism is integrated with the constructor/destructor mechanisms and the concurrency mechanisms to help ensure that the returning function must leave the program in a good state and not leak any resources.
The exception-handling mechanism:
* Is an alternative to the tradition techniques when they are insufficient, inelegant, or error-prone.
* Is complete; It can be used to detect all errors detected by ordinary code.
* Allows the programmer to explicitly separate error-handling code from "ordinary-code", thus making the program more readable and more amenable to tools.
* Supports a more regular style of error handling, thus simplify cooperation between separately written program fragments.

An exception is an object thrown to represent the occurrence of an error. An exception can be of any type that can be copied, but it is strongly recommended to use only user-defined types specifically defined for that purpose.
Thus the simplest way of defining an exception is to define a class specifically for a kind of eror.

