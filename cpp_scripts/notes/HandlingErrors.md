#Handling errors, cerr and exit
Errors fall into two categories: synatx and semantic errors.
###Syntax errors
A syntax error occurs when you write a statement that is not valid according to the grammar of the C++ language. Syntax errors are almost always caught by the compiler and are usually easy to fix.
###Semantic errors
A semantic error occurs when a statement is syntatically valid, but does not do what the programmer intended.
Semantic errors are not caught by compilers, and can have any number of effects: they may not show up at all, cause the program to produce the wrong output, cause erratic behavior, corrupt data, or cause the program to crash.
Semantic errors can occur in a number of ways. One of the most common semantic errors is a logic error. A logic
error occurs when the programmer incorrectly codes the logic of a statement.
Another common semantic error is the violated assumption. A violated assumption occurs when the programmer assumes that something will be either true or false, and it isn't.

###Defensive programming
Defensive programming is a form of program design that involves trying to identify areas where assumptions may be violated, and writing code that detects and handles any violation of those assumptions so that the program reacts in a predictable way when those violations do occur.
###Detecting assumption errors
We can catch almost all assumptions that need to be checked in one of the three locations:
- When a function has been called, the caller may have passed the function parameters that are incorrect or semantically meaningless.
- When a function returns, the return value may indicate that an error has occurred.
- When program receives input (either from the user, or a file), the input may not be in the correct format.
Consequently, the following rules should be used when programming defensively:
- At the tope of each function, check to make sure any parameters have appropriate values.
- After a function has returned, check the return value (if any), and any other error reporting mechanisms, to see if an error occurred.
- Validate any user input to make sure it meets the expected formatting or range criteria.

###Handling assumption errors:
- Quietly skip the code that depends on the assumption being valid.
- If we are in a function, return an error code back to the caller and let the caller deal with the problem.
- If we want to terminate the program immediately, teh exit function that lives in <cstdlib> can be used to return an error code to the operating system.
- If the user have entered invalid input, ask the user to enter the input again.
- `cerr` is another mechanism that is meant specifically for printing error messages. `cerr` is an output stream that is defined in `<iostream>`. Typically, cerr writes the error messages on the screen (just like cout), but it can also be individually redirected to a file.
-If working in some kind of graphical environment, it is common to pop up a message box with an error code and then terminate the program.
